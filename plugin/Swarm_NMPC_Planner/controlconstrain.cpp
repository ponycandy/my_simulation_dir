#include "controlconstrain.h"

#include "xmlcore.h"
#include "automated_gradient.h"
#include "Matrix_sparser.h"
ControlConstrain::ControlConstrain(int num,std::string &name):ConstraintSet(num,name)
{
    //两个约束，第一是相邻点距离约束，第二个是时间约束
    m_poly=new PolyParams;
    m_poly->initilization();
    QString configfiename="./config/Polys/constrainParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("steps",dec_num);
    xml_reader.xmlRead("pointnum",pointNum);
    xml_reader.xmlRead("step_time",steptime);
    xml_reader.xmlRead("agentnum",agentnum);
    xml_reader.xmlRead("Radius",miniRadius);


    consnum=num;
    constrainIndex=dec_num;
}

ifopt::Component::VectorXd ControlConstrain::GetValues() const
{

    //
    QString var_name;
    VectorXd g(GetRows());

    var_name="spline_p_set_of_"+QString::number(current_agent_num);
    Eigen::VectorXd x=GetVariables()->GetComponent(var_name.toStdString())->GetValues();
    m_poly->packvariable(x);
    FillinG(g);
    return g;
}

ifopt::Component::VecBound ControlConstrain::GetBounds() const
{
    VecBound b(GetRows());
    for(int i=1;i<=constrainIndex+1;i++)
    {
        b.at(i-1)=ifopt::BoundSmallerZero;
    }
    b.at(constrainIndex)=ifopt::BoundZero;
    for(int i=0;i<pointNum;i++)
    {
        b.at(constrainIndex+i+1)=ifopt::BoundGreaterZero;
    }
    return b;
}

void ControlConstrain::GetValue(Eigen::VectorXd &x, Eigen::VectorXd &returnvalue) const
{
    m_poly->packvariable(x);
    returnvalue.resize(consnum);
    pos_and_derivative x_x;
    pos_and_derivative x_y;
    double total_T=0;
    for(int i=0;i<dec_num;i++)
    {
        double vx=m_poly->Get_Single_Speed_any(i*steptime,0);
        double vy=m_poly->Get_Single_Speed_any(i*steptime,1);
        double speed_max=vx*vx+vy*vy;
        returnvalue(i)=speed_max-miniRadius*miniRadius;
    }
    for(int i=0;i<pointNum;i++)
    {

        m_poly->Get_pos_and_derivative_set(i,x_x,0);

        total_T+=x_x.lasting_time;
        returnvalue(constrainIndex+i+1)=x_x.lasting_time;
    }
    returnvalue(constrainIndex)=total_T-dec_num*steptime;
}

void ControlConstrain::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    QString var_name;
    var_name="spline_p_set_of_"+QString::number(current_agent_num);
    if (var_set == var_name.toStdString())
    {
        pos_and_derivative setx;
        Eigen::VectorXd x=GetVariables()->GetComponent(var_name.toStdString())->GetValues();
        m_poly->packvariable(x);
        Jac_Group group;
        single_jacob jac0;
        group.init(1);
        for(int i=0;i<dec_num;i++)
        {
//            jac0.relative_2_dec=i;
//            Eigen::MatrixXd mid;
//            mid.resize(1,2);
//            double vx=m_poly->Get_Single_Speed_any(i*steptime,0);
//            double vy=m_poly->Get_Single_Speed_any(i*steptime,1);
//            mid<<2*vx,2*vy;
//            jac0.jacobian=mid;
//            group.jac_sets[0]=jac0;
//            m_poly->FillinJacobian(jac_block,group);
//这个矩阵显然是错误的
        }
        m_poly->clearconstrainindex();
        for(int i=0;i<pointNum;i++)
        {
            //时间约束
            m_poly->Get_pos_and_derivative_set(i,setx,0);
            jac_block.coeffRef(constrainIndex,setx.lasting_time_index)+=1;
            jac_block.coeffRef(constrainIndex+i+1,setx.lasting_time_index)=1;
        }
        jac_block.makeCompressed();

        Automated_Gradient calcer;
        Eigen::MatrixXd jacob;

        calcer.GetGradient(x,dynamic_cast< const AutoCalc *>(this),jacob);

        std::cout<<"-----------------numerical -   results   -  down --here   ----------------------"<<std::endl;
        std::cout<<jacob<<std::endl;
        std::cout<<"-----------------numerical -   results   -  up  --here    ----------------------"<<std::endl;
        std::cout<<"-----------------Analytical -   results   -  down  --here    ----------------------"<<std::endl;
        std::cout<<jac_block<<std::endl;
        std::cout<<"-----------------Analytical -   results   -  up  --here    ----------------------"<<std::endl;
        std::cout<<"-----------------relative bias is below    ----------------------"<<std::endl;
        Eigen::MatrixXd matyup;
        matyup=jac_block-jacob;
        std::cout<<matyup<<std::endl;
        std::cout<<" "<<std::endl;
        jac_block=jacob.sparseView();

    }


}

void ControlConstrain::FillinG(Eigen::VectorXd &g) const
{
    pos_and_derivative x_x;
    pos_and_derivative x_y;
    double total_T=0;
    //等一下，当初执行下面的距离约束一定程度上就是因为
    //速度约束太复杂导致的
    //这样的话会不会导致问题反而无法求解？
    //尝试逐点添加速度约束
    for(int i=0;i<dec_num;i++)
    {
        double vx=m_poly->Get_Single_Speed_any(i*steptime,0);
        double vy=m_poly->Get_Single_Speed_any(i*steptime,1);
        double speed_max=vx*vx+vy*vy;
        g(i)=speed_max-miniRadius*miniRadius;
    }
        for(int i=0;i<pointNum;i++)
        {

            m_poly->Get_pos_and_derivative_set(i,x_x,0);

            total_T+=x_x.lasting_time;
            g(constrainIndex+i+1)=x_x.lasting_time;
        }
        //时间约束:
        g(constrainIndex)=total_T-dec_num*steptime;
    //据此填写jacob矩阵
}
