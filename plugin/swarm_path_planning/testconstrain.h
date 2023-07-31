#ifndef TESTCONSTRAIN_H
#define TESTCONSTRAIN_H
#include "ifopt/constraint_set.h"
//this is a constrain that do nothing!
class TestConstrain:public ifopt::ConstraintSet
{
public:
    TestConstrain(int num);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void FillHessionBlock(std::string var_set, Jacobian& jac_block,int irow) const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    mutable int constrainnum;
};

#endif // TESTCONSTRAIN_H
