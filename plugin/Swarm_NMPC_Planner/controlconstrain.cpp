#include "controlconstrain.h"

#include "xmlcore.h"
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



    constrainIndex=num-1;
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

    return b;
}

void ControlConstrain::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    QString var_name;
    var_name="spline_p_set_of_"+QString::number(current_agent_num);
    if (var_set == var_name.toStdString())
    {
        pos_and_derivative setx;
        pos_and_derivative sety;
        Eigen::VectorXd x=GetVariables()->GetComponent(var_name.toStdString())->GetValues();
        m_poly->packvariable(x);
        for(int i=0;i<pointNum;i++)
        {
            m_poly->Get_pos_and_derivative_set(i,setx,0);
            m_poly->Get_pos_and_derivative_set(i,sety,1);
            if(i>0)
            {
                jac_block.coeffRef(i,setx.start_point.point_value_index)+=2*(setx.x0-setx.x1);
                jac_block.coeffRef(i,sety.start_point.point_value_index)+=2*(sety.x0-sety.x1);
            }
            jac_block.coeffRef(i,setx.end_point.point_value_index)+=2*(-setx.x0+setx.x1);
            jac_block.coeffRef(i,sety.end_point.point_value_index)+=2*(-sety.x0+sety.x1);
            //单个节点信息
            //单个控制段信息
            //每个控制段信息由两个节点决定
            //这样可以稍微增加index管理的便利度
            //时间约束
            jac_block.coeffRef(constrainIndex,setx.lasting_time_index)+=1;
        }
        jac_block.makeCompressed();
    }


}

void ControlConstrain::FillinG(Eigen::VectorXd &g) const
{
    pos_and_derivative x_x;
    pos_and_derivative x_y;
    double total_T=0;
    //相邻距离约束:
    for(int i=0;i<pointNum;i++)
    {

        m_poly->Get_pos_and_derivative_set(i,x_x,0);
        m_poly->Get_pos_and_derivative_set(i,x_y,1);
        g(i)=pow(x_x.x0-x_x.x1,2)+pow(x_y.x0-x_y.x1,2)-miniRadius*miniRadius;
        total_T+=x_x.lasting_time;
    }
    //时间约束:
    g(constrainIndex)=total_T-dec_num*steptime;
    //据此填写jacob矩阵

}
