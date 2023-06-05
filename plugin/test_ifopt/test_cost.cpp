#include "test_cost.h"



test_cost::test_cost(): CostTerm("cost")
{

}

double test_cost::GetCost() const
{
    Eigen::Vector2d x = GetVariables()->GetComponent("var_set1")->GetValues();
    return -std::pow(x(1)-2,2);
}

void test_cost::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{
    if (var_set == "var_set1")
    {
        Eigen::Vector2d x = GetVariables()->GetComponent("var_set1")->GetValues();

        jac.coeffRef(0, 0) = 0.0;             // derivative of cost w.r.t x0
        jac.coeffRef(0, 1) = -2.0*(x(1)-2.0); // derivative of cost w.r.t x1
    }
}
