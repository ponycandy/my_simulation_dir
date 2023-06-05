#ifndef TESTCONS_H
#define TESTCONS_H
#include <ifopt/constraint_set.h>

class testCons: public ifopt::ConstraintSet
{
public:
    testCons(int num);
    void counts();
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    int member;
};

#endif // TESTCONS_H
