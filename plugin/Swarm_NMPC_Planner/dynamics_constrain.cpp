#include "dynamics_constrain.h"
#include "var_packer.h"
#include "QString"
#include "Matrix_sparser.h"
Dynamics_Constrain::Dynamics_Constrain(int num):ConstraintSet(num,"Dynamics_Constrain")
{
    QString configfiename="./config/Polys/ProblemParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("dim",dims);
    xml_reader.xmlRead("steps",decnum);
    xml_reader.xmlRead("pointnum",pointnum);
    xml_reader.xmlRead("step_time",steptime);
    xml_reader.xmlRead("agentnum",agentnum);
}

ifopt::Component::VectorXd Dynamics_Constrain::GetValues() const
{
    QString var_name;
    VectorXd g(GetRows());
    for(int i=0;i<agentnum;i++)
    {
        var_name="spline_p_set_of_"+QString::number(i);
        m_polys[i].packvariable(GetVariables()->GetComponent(var_name)->GetValues());
    }
    packvariable_states_set(GetVariables()->GetComponent("state_vars")->GetValues(),states,decnum );
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

void Dynamics_Constrain::Fill_dynamics_Jacob(Jacobian &jac)
{
    Eigen::MatrixXd A_mat,B_mat;
    Eigen::MatrixXd Identi;
    Identi.resize(statenum,statenum);
    Identi.setIdentity();
    Eigen::MatrixXd dfd1;
    Eigen::MatrixXd dadpt;

    Matrix_sparser mat_sparse;
    for(int i=0;i<decnum;i++)
    {
        if(i>0)
        {
        self_jacobian->get_A_and_B(actMat.block(0,i,actnum,1),states.block(0,i,statenum,1),A_mat,B_mat);

        Calc_a_2_pt(dadpt,states.block(0,i,statenum,1),i);

        mat_sparse->Copy_Mat_2_Sparse_block(jac,Identi,statenum*i,statenum*(i),statenum,statenum);
        dfd1=-Identi-steptime*A_mat+steptime*B_mat*dadpt;
        mat_sparse->Copy_Mat_2_Sparse_block(jac,dfd1,statenum*i,statenum*(i-1),statenum,statenum);

        }
        else
        {
        self_jacobian->get_A_and_B(actMat.block(0,i,actnum,1),initstates_of_animals,A_mat,B_mat);
        mat_sparse->Copy_Mat_2_Sparse_block(jac,Identi,0,0,statenum,statenum);
        }
    }
}

void Dynamics_Constrain::Fill_dynamics_action(Jacobian &jac)
{
    PolyParams set=m_polys[current_agent];
    Jac_Group group;
    single_jacob jac0;
    Eigen::MatrixXd A_mat;
    Eigen::MatrixXd B_mat;
    Eigen::MatrixXd dadpi;
    for(int i=0;i<decnum;i++)
    {
        self_jacobian->get_A_and_B(actMat.block(0,i,2,1)
                                   ,states.block(0,i,statenum,1),A_mat,B_mat);

        jac0.relative_2_dec=i;
        Calc_a_2_pi(dadpi,states.block(0,i,2,1),i,current_agent);
        jac0.jacobian=-steptime*B_mat*dadpi;
        group[0]=jac0;
        set.FillinJacobian(jac,group);
// 我想我们需要三级，乃至多级的雅可比矩阵计算！雅可比的级数
//也需要可变
    }
}

void Dynamics_Constrain::Calc_a_2_pi(Eigen::MatrixXd &mat, Eigen::MatrixXd &pt, int decN, int agentindex)
{
    Eigen::MatrixXd eye_2;
    Eigen::MatrixXd dfdpi;
    Eigen::MatrixXd pi=ActMats[agentindex].block(0,decN,2,1);
    dfdpi(0,0)=2*(pi(0,0)-pt(0,0));//1*2矩阵
    dfdpi(0,1)=2*(pi(1,0)-pt(1,0));
    double fnorm=dec_2_coef_map[agentindex][decN];
    mat=-eye_2*coef_K/fnorm+(pt-)*coef/(-fnorm*fnorm)*dfdpi;
}

void Dynamics_Constrain::Calc_a_2_pt(Eigen::MatrixXd &mat, Eigen::MatrixXd &pt,int decN)
{
    Eigen::MatrixXd eye_2;
    Eigen::MatrixXd dfdpt;
    double f_norm;
    for(int j=0;j<agentnum;j++)
    {
        f_norm=dec_2_coef_map[j][dec];
        Eigen::MatrixXd pi=ActMats[j][decN];
        dfdpt=2*(pt-pi);//1*2矩阵
        mat+=(eye_2*coef_K/f_norm+(pi-pt)*(coef_K/(f_norm*f_norm))*dfdpt;
    }
}

void Dynamics_Constrain::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    //下面的矩阵实际上无需反复求算，可以在初始化的时候搞定然后
    //赋值给jac_block
    if (var_set == "state_vars")
    {
        packvariable_states_set(GetVariables()->GetComponent("state_vars")->GetValues(),states,decnum );
        formactmat();
        Fill_dynamics_Jacob(jac_block);
    }
    for(int j=0;j<agentnum;j++)
    {
        QString var_name;
        var_name="spline_p_set_of_"+QString::number(j);
        if (var_set == var_name)
        {
            m_polys[j].packvariable(GetVariables()->GetComponent(var_name)->GetValues());
            Fill_dynamics_action(jac_block);
            break;
        }

    }
}

void Dynamics_Constrain::FillinG(Eigen::VectorXd &g)
{
    for(int i=0;i<decnum;i++)
    {
        if(i==0)
        {
            Combined_cons.block(0,0,statenum,1)=states.block(0,0,statenum,1)-initstates_of_animals-steptime*self_ode->ode_function(actMat.block(0,0,actnum,1),initstates_of_animals);
        }
        else
        {
            Combined_cons.block(statenum*i,0,statenum,1)=states.block(0,i,statenum,1)-states.block(0,i-1,statenum,1)-steptime*self_ode->ode_function(actMat.block(0,i,actnum,1),states.block(0,i-1,statenum,1));
        }
    }
    for(int i=0;i<constrainnum;i++)
    {
        g(i)=Combined_cons(i);
    }
}

void Dynamics_Constrain::formactmat()
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
        double norm_2_sqrt;
        for(int i=0;i<decnum;i++)
        {
            mid_1=states.block(0,i,2,1)-single_mat.block(0,i,2,1);
            norm_2_sqrt=mid_1(0,0)*mid_1(0,0)+mid_1(1,0)*mid_1(1,0);
            actMat.block(0,i,2,1)+=((coef_K*mid_1)/norm_2_sqrt);
            dec_2_coef_map[j][i]=norm_2_sqrt;
        }
    }
}
