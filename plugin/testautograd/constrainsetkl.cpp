#include "constrainsetkl.h"

constrainsetkl::constrainsetkl(int num):ifopt::ConstraintSet(num,"constest")
{

}

ifopt::Component::VectorXd constrainsetkl::GetValues() const
{
    QString var_name;
    VectorXd g(GetRows());

    var_name="x_value_all";
    Eigen::VectorXd x=GetVariables()->GetComponent(var_name.toStdString())->GetValues();

//    m_poly->packvariable(x);
//    FillinG(g);
    return g;
}

ifopt::Component::VecBound constrainsetkl::GetBounds() const
{

}

void constrainsetkl::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{

}
