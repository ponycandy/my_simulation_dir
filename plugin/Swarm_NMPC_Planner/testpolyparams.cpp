
#include "testpolyparams.h"
#include "xmlcore.h"

TestPolyParams::TestPolyParams(int num):ConstraintSet(num,"testpoly")
{
    m_poly=new PolyParams;
    m_poly->initilization();
    QString configfiename="./config/Polys/constrainParams.xml";
    xmlCore xml_reader(configfiename.toStdString());
    xml_reader.xmlRead("steps",dec_num);
    xml_reader.xmlRead("pointnum",pointNum);
    xml_reader.xmlRead("step_time",steptime);
    xml_reader.xmlRead("agentnum",agentnum);
    xml_reader.xmlRead("Radius",miniRadius);
    actmat.resize(2,dec_num);
    endindex=4;
    startindex=endindex-1;
}

ifopt::Component::VectorXd TestPolyParams::GetValues() const
{
    QString var_name;
    VectorXd g(GetRows());

    var_name="spline_p_set_of_"+QString::number(0);
    Eigen::VectorXd x=GetVariables()->GetComponent(var_name.toStdString())->GetValues();
    m_poly->packvariable(x);
    FillinG(g);
    return g;
}

ifopt::Component::VecBound TestPolyParams::GetBounds() const
{
    VecBound b(GetRows());

    b.at(0)=ifopt::BoundZero;
//    b.at(1)=ifopt::BoundZero;


    return b;
}

void TestPolyParams::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    QString var_name;
    var_name="spline_p_set_of_"+QString::number(0);
    if (var_set == var_name.toStdString())
    {

        Eigen::VectorXd x=GetVariables()->GetComponent(var_set)->GetValues();
        m_poly->packvariable(x);
//        Jac_Group group;
//        group.init(2);

//        single_jacob jacob_1;
//        jacob_1.relative_2_dec=startindex;
//        jacob_1.jacobian.resize(2,2);
//        jacob_1.jacobian<<-1,0,0,-1;
//        group.jac_sets[0]=jacob_1;

//        single_jacob jacob_2;
//        jacob_2.relative_2_dec=endindex;
//        jacob_2.jacobian.resize(2,2);
//        jacob_2.jacobian<<1,0,0,1;
//        group.jac_sets[1]=jacob_2;
//        m_poly->FillinJacobian(jac_block,group);
//        m_poly->clearconstrainindex();


        Jac_Group group;
        group.init(2);

        single_jacob jacob_1;
        jacob_1.relative_2_dec=startindex;
        jacob_1.jacobian.resize(1,2);
        jacob_1.jacobian<<-1,0;
        group.jac_sets[0]=jacob_1;

        single_jacob jacob_2;
        jacob_2.relative_2_dec=endindex;
        jacob_2.jacobian.resize(1,2);
        jacob_2.jacobian<<1,0;
        group.jac_sets[1]=jacob_2;
        m_poly->FillinJacobian(jac_block,group);
        m_poly->clearconstrainindex();

    }
}

void TestPolyParams::FillinG(Eigen::VectorXd &g) const
{
    pos_and_derivative x_x;
    pos_and_derivative x_y;
    //相邻距离约束:
    m_poly->Get_Poly_Value_Mat(actmat);
    g(0)=actmat(0,endindex)-actmat(0,startindex)-1;
//    g(1)=actmat(1,endindex)-actmat(1,startindex)-1;
}
