#ifndef VARIABLEXL_H
#define VARIABLEXL_H

#include "ifopt/variable_set.h"

class variablexl:public ifopt::VariableSet
{
public:
    variablexl(int num );
    void SetVariables(const VectorXd& x);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    mutable Eigen::VectorXd data;
};

#endif // VARIABLEXL_H
