#include "costtermas.h"
#include "iostream"
CostTermas::CostTermas(std::string name):ifopt::CostTerm(name)
{

}

double CostTermas::GetCost() const
{
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    std::cout<<x<<std::endl;
    return (x(10)-1)*(x(10)-1);
}

void CostTermas::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();

    jac.coeffRef(0,10)=2*(x(10)-1);
}

void CostTermas::FillHessionBlock(std::string var_set, Jacobian &jac_block, int irow) const
{
    //问题复现
    jac_block.coeffRef(10,10)=2;
}
