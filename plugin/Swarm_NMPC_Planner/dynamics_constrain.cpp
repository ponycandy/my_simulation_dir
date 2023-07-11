#include "dynamics_constrain.h"
#include "var_packer.h"
#include "QString"
#include "Matrix_sparser.h"
#include "jacobian_state.h"
Dynamics_Constrain::Dynamics_Constrain(int num):ConstraintSet(num,"Dynamics_Constrain")
{
    QString configfiename="./config/Polys/constrainParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("steps",decnum);
    xml_reader.xmlRead("pointnum",pointnum);
    xml_reader.xmlRead("step_time",steptime);
    xml_reader.xmlRead("agentnum",agentnum);
    xml_reader.xmlRead("statenum",statenum);
    xml_reader.xmlRead("actnum",actnum);
    xml_reader.xmlRead("Coef",coef_K);
    initstates_of_animals.resize(statenum,1);
    xml_reader.xmlRead("Initstate",initstates_of_animals);
    //这里注意矩阵的固定格式，是tab+enter换行，首尾开始和结束时各换一次行，
    //矩阵换行时同时换行，如下：
    //    <Initstate type="Eigen::MatrixXd">
    //        <value>
    //        2.0
    //        2.0
    //        0.0
    //        0.0
    //        </value>
    //        </Initstate>
    //换行用tab+enter，不要加空格！！
    //元素之间可以有多个空格吗，这个无影响



    constrainnum=num;
    init_num(statenum,agentnum,decnum,pointnum,steptime);
    self_jacobian=new Jacobian_state;
    actMat.resize(actnum,decnum);
    actMat.setZero();
    states.resize(statenum,decnum);
    states.setZero();
    A_mat.resize(statenum,statenum);
    B_mat.resize(statenum,actnum);
    current_agent=0;
    Eigen::MatrixXd actmats_i;
    actmats_i.resize(2,decnum);
    actmats_i.setZero();
    dec_2_coef_map.resize(agentnum,decnum);
    dec_2_coef_map.setOnes();
    for(int i=0;i<agentnum;i++)
    {
        ActMats.insert(i,actmats_i);
    }

    for(int j=0;j<agentnum;j++)
    {
        for(int i=0;i<decnum;i++)
        {
            dec_2_coef_map(j,i)=1;
        }
    }
    Combined_cons.resize(constrainnum,1);


}

ifopt::Component::VectorXd Dynamics_Constrain::GetValues() const
{
    QString var_name;
    VectorXd g(GetRows());
    for(int i=0;i<agentnum;i++)
    {
        var_name="spline_p_set_of_"+QString::number(i);
        Eigen::VectorXd x=GetVariables()->GetComponent(var_name.toStdString())->GetValues();
        m_polys[i].packvariable(x);
    }
    Eigen::VectorXd x;
    x.resize(statenum*decnum);
    x=GetVariables()->GetComponent("state_value")->GetValues();
    packvariable_states_set(x,states,decnum);
    formactmat();
    FillinG(g);

    return g;
}


void Dynamics_Constrain::init_num(int state_num, int agent_num, int dec_num, int pointnum,double step) const
{
    agentnum=agent_num;
    steptime=step;
    for(int j=0;j<agent_num;j++)
    {
        PolyParams single_poly;
        single_poly.configfiename="./config/Polys/constrainParams"+QString::number(j)+".xml";
        single_poly.initilization();
        m_polys.insert(j,single_poly);
    }
}


ifopt::Component::VecBound Dynamics_Constrain::GetBounds() const
{
    VecBound b(GetRows());

    for(int i=1;i<=constrainnum;i++)
    {
        b.at(i-1)=ifopt::Bounds(0.0, 0.0);
    }

    return b;
}

void Dynamics_Constrain::Fill_dynamics_Jacob(Jacobian &jac) const
{
    Eigen::MatrixXd Identi;
    Identi.resize(statenum,statenum);
    Identi.setIdentity();
    Eigen::MatrixXd dfd1;
    Eigen::MatrixXd dadpt;
    dadpt.resize(2,4);
    Matrix_sparser mat_sparse;
    for(int i=0;i<decnum;i++)
    {
        if(i>0)
        {
            self_jacobian->get_A_and_B(actMat.block(0,i,actnum,1),states.block(0,i,statenum,1),A_mat,B_mat);
            Eigen::MatrixXd mid=states.block(0,i,2,1);
            dadpt.setZero();
            Calc_a_2_pt(dadpt,mid,i);
            mat_sparse.Copy_Mat_2_Sparse_block(jac,Identi,statenum*i,statenum*(i),statenum,statenum);
            dfd1=-Identi-steptime*A_mat-steptime*B_mat*dadpt;
            mat_sparse.Copy_Mat_2_Sparse_block(jac,dfd1,statenum*i,statenum*(i-1),statenum,statenum);

        }
        else
        {
            self_jacobian->get_A_and_B(actMat.block(0,i,actnum,1),initstates_of_animals,A_mat,B_mat);
            mat_sparse.Copy_Mat_2_Sparse_block(jac,Identi,0,0,statenum,statenum);
        }
    }
}

void Dynamics_Constrain::Fill_dynamics_action(Jacobian &jac) const
{
    PolyParams set=m_polys[current_agent];
    Jac_Group group;
    single_jacob jac0;
    group.init(1);
    Eigen::MatrixXd dadpi;
    dadpi.resize(2,2);
    for(int i=0;i<decnum;i++)
    {
        self_jacobian->get_A_and_B(actMat.block(0,i,2,1),states.block(0,i,statenum,1),A_mat,B_mat);

        jac0.relative_2_dec=i;
        Eigen::MatrixXd mid=states.block(0,i,2,1);
        dadpi.setZero();
        Calc_a_2_pi(dadpi,mid,i,current_agent);
        jac0.jacobian=-steptime*B_mat*dadpi;
        group.jac_sets[0]=jac0;
        set.FillinJacobian(jac,group);
        // 我想我们需要三级，乃至多级的雅可比矩阵计算！雅可比的级数
        //也需要可变
    }


}

void Dynamics_Constrain::Calc_a_2_pi(Eigen::MatrixXd &mat, Eigen::MatrixXd &pt, int decN, int agentindex) const
{
    Eigen::MatrixXd eye_2;
    eye_2.resize(2,2);
    eye_2<<1,0,0,1;
    Eigen::MatrixXd dfdpi;
    dfdpi.resize(1,2);
    Eigen::MatrixXd pi=ActMats[agentindex].block(0,decN,2,1);
    dfdpi(0,0)=2*(pi(0,0)-pt(0,0));//1*2矩阵
    dfdpi(0,1)=2*(pi(1,0)-pt(1,0));
    double fnorm=dec_2_coef_map(agentindex,decN);
    mat=-eye_2*coef_K/fnorm+(pt-pi)*coef_K/(-fnorm*fnorm)*dfdpi;//2*2矩阵
}

void Dynamics_Constrain::Calc_a_2_pt(Eigen::MatrixXd &mat, Eigen::MatrixXd &pt,int decN) const
{
    Eigen::MatrixXd eye_2;
    eye_2.resize(2,2);
    eye_2<<1,0,0,1;
    Eigen::MatrixXd dfdpt;
    dfdpt.resize(1,2);
    double f_norm;
    for(int j=0;j<agentnum;j++)
    {
        f_norm=dec_2_coef_map(j,decN);
        Eigen::MatrixXd pi=ActMats[j].block(0,decN,2,1);
        dfdpt(0,0)=2*(pt(0,0)-pi(0,0));//1*2矩阵
        dfdpt(0,1)=2*(pt(1,0)-pi(1,0));

        mat.block(0,0,2,2)+=(eye_2*coef_K/f_norm)+(pi-pt)*(coef_K/(f_norm*f_norm))*dfdpt;
    }
}

void Dynamics_Constrain::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    //下面的矩阵实际上无需反复求算，可以在初始化的时候搞定然后
    //赋值给jac_block


    if (var_set == "state_value")
    {
        Eigen::VectorXd x=GetVariables()->GetComponent("state_value")->GetValues();
        packvariable_states_set(x,states,decnum );

        for(int j=0;j<agentnum;j++)
        {
            QString var_name;
            var_name="spline_p_set_of_"+QString::number(j);
            Eigen::VectorXd x=GetVariables()->GetComponent(var_set)->GetValues();
            current_agent=j;
            m_polys[current_agent].packvariable(x);

        }
        formactmat();

        Fill_dynamics_Jacob(jac_block);
    }
    for(int j=0;j<agentnum;j++)
    {
        QString var_name;
        var_name="spline_p_set_of_"+QString::number(j);
        if (var_set == var_name.toStdString())
        {
            current_agent=j;
            Fill_dynamics_action(jac_block);
            m_polys[current_agent].clearconstrainindex();
            break;
        }
    }
}

void Dynamics_Constrain::FillinG(Eigen::VectorXd &g) const
{
    for(int i=0;i<decnum;i++)
    {
        if(i==0)
        {
            Combined_cons.block(0,0,statenum,1)=states.block(0,0,statenum,1)-initstates_of_animals-steptime*self_jacobian->ode_function(actMat.block(0,0,actnum,1),initstates_of_animals);
        }
        else
        {
            Combined_cons.block(statenum*i,0,statenum,1)=states.block(0,i,statenum,1)-states.block(0,i-1,statenum,1)-steptime*self_jacobian->ode_function(actMat.block(0,i,actnum,1),states.block(0,i-1,statenum,1));
        }
    }
    for(int i=0;i<constrainnum;i++)
    {
        g(i)=Combined_cons(i);
    }
    //多依赖非线性求解的一个问题，单个变量组不会触发所有的依赖迭代
}

void Dynamics_Constrain::formactmat() const
{
    for(int i=0;i<agentnum;i++)
    {
        m_polys.value(i).Get_Poly_Value_Mat(ActMats[i]);
    }
    actMat.setZero();
    Eigen::MatrixXd single_mat;
    Eigen::MatrixXd mid_1;
    //推导这里的导数的时候，注意，常数和向量左右顺序是有关系的
    //常数必须被放在右边然后求导
    for(int j=0;j<agentnum;j++)
    {
        single_mat=ActMats.value(j);
        Eigen::MatrixXd statepn;
        //初始追踪轨迹已经被压入了ActMats
        double norm_2_sqrt;
        for(int i=0;i<decnum;i++)
        {
            if(i==0)
            {
                statepn=initstates_of_animals.block(0,0,2,1);
            }
            else
            {
                statepn=states.block(0,i-1,2,1);
            }
            mid_1=statepn-single_mat.block(0,i,2,1);
            norm_2_sqrt=mid_1(0,0)*mid_1(0,0)+mid_1(1,0)*mid_1(1,0);
            actMat.block(0,i,2,1)+=((coef_K*mid_1)/norm_2_sqrt);
            dec_2_coef_map(j,i)=norm_2_sqrt;
            //初始状态没有被加载....
        }
    }
}
