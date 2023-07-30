#ifndef CONSTRAINTEST_H
#define CONSTRAINTEST_H
#include "ifopt/constraint_set.h"

class constraintest:public ifopt::ConstraintSet
{
public:
    constraintest(int num,std::string name);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    void FillHessionBlock (std::string var_set, Jacobian& jac,int irow) const override;


};

#endif // CONSTRAINTEST_H
