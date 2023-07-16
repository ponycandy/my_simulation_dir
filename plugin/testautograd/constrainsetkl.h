#ifndef CONSTRAINSETKL_H
#define CONSTRAINSETKL_H
#include "ifopt/constraint_set.h"
#include "QObject"
#include "QString"
#include "autograd/variablematrix.h""
class constrainsetkl:public ifopt::ConstraintSet
{
public:
    constrainsetkl(int num);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;

};

#endif // CONSTRAINSETKL_H
