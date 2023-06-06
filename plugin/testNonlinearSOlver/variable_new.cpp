#include "variable_new.h"

Variable_new::Variable_new():VariableSet(1, "test_extra_var")
{
    x0=0;
}

void Variable_new::SetVariables(const VectorXd &x)
{
    x0=x(0);
}

ifopt::Component::VectorXd Variable_new::GetValues() const
{
    Eigen::VectorXd all_variable(1);
    all_variable(0)=x0;
    return all_variable;
}

ifopt::Component::VecBound Variable_new::GetBounds() const
{
    ifopt::Component::VecBound bounds(GetRows());

    bounds.at(0)=ifopt::NoBound;

    return bounds;
}
