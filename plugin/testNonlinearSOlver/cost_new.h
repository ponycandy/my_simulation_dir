#ifndef COST_NEW_H
#define COST_NEW_H

#include <ifopt/cost_term.h>
class cost_New:public ifopt::CostTerm
{
public:
    cost_New();
    double GetCost() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac) const override;
};

#endif // COST_NEW_H
//public CostTerm {
//public:
//    ExCost() : ExCost("cost_term1") {}
//    ExCost(const std::string& name) : CostTerm(name) {}

//    double GetCost() const override
//    {
//        Vector2d x = GetVariables()->GetComponent("var_set1")->GetValues();
//        return -std::pow(x(1)-2,2);
//    };

//    void FillJacobianBlock (std::string var_set, Jacobian& jac) const override
//    {
//        if (var_set == "var_set1") {
//            Vector2d x = GetVariables()->GetComponent("var_set1")->GetValues();

//            jac.coeffRef(0, 0) = 0.0;             // derivative of cost w.r.t x0
//            jac.coeffRef(0, 1) = -2.0*(x(1)-2.0); // derivative of cost w.r.t x1
//        }
//    }
//};
