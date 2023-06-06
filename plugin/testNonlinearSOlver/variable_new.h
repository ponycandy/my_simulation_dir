#ifndef VARIABLE_NEW_H
#define VARIABLE_NEW_H

#include <ifopt/variable_set.h>
class Variable_new:public ifopt::VariableSet
{
public:
    Variable_new();
    void SetVariables(const VectorXd& x);
    VectorXd GetValues() const override;
    // Each variable has an upper and lower bound set here
    VecBound GetBounds() const override;
    mutable double x0;
};

#endif // VARIABLE_NEW_H
