#ifndef TEST_COST_H
#define TEST_COST_H

#include <ifopt/cost_term.h>
class test_cost:public ifopt::CostTerm
{
public:
    test_cost();
    double GetCost() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac) const override;
};

#endif // TEST_COST_H
