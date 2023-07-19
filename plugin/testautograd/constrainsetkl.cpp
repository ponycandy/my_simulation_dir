#include "constrainsetkl.h"

constrainsetkl::constrainsetkl(int num):ifopt::ConstraintSet(num,"constest")
{
    m_variable.resize(5,1);//假设变量为x1~x5
    eigendata.resize(5,5);
    eigendata<<2 , 1 , 0 , 0.7 , 9,
               1 , 1 , -3 , 0.8 ,0,
               0 , -3 , 3 , 0.8 ,0,
               0.7,0.8,0.8, 0   ,0,
                9 ,0 ,0 , 0   , 0;
}

ifopt::Component::VectorXd constrainsetkl::GetValues() const
{
//    QString var_name;
//    VectorXd g(GetRows());

//    var_name="x_value_all";
//    Eigen::VectorXd x=GetVariables()->GetComponent(var_name.toStdString())->GetValues();
//    for(int i=0;i<x.rows();i++)
//    {
//        m_variable[i][0]=autograd::variable(1);
//    }

//   ATtensor outcome=m_variable.Transpose() * eigendata * m_variable;
//    return outcome[0][0]->value_;
}

ifopt::Component::VecBound constrainsetkl::GetBounds() const
{

}

void constrainsetkl::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{

}
