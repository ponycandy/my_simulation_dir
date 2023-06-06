#include "cost_new.h"

cost_New::cost_New():CostTerm("minimize_energy_cost")
{

}

double cost_New::GetCost() const
{
    Eigen::VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    return x(0)*x(0);
}

void cost_New::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{
    if (var_set == "action_state_set1")
    {
        Eigen::VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();

        jac.coeffRef(0, 0) = 2*x(0);
    }
}
