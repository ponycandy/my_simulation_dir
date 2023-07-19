#ifndef CONSTRAINSETKL_H
#define CONSTRAINSETKL_H
#include "ifopt/constraint_set.h"
#include "QObject"
#include "QString"
#include "autograd/variablematrix.h"
#include "Eigen/core"
class constrainsetkl:public ifopt::ConstraintSet
{
public:
    constrainsetkl(int num);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    mutable ATtensor m_variable;
    mutable Eigen::MatrixXd eigendata;
};

#endif // CONSTRAINSETKL_H
