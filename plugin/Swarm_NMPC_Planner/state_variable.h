#ifndef STATE_VARIABLE_H
#define STATE_VARIABLE_H

#include "ifopt/variable_set.h"
class State_Variable:public ifopt::VariableSet
{
public:
    State_Variable(int num ,std::string& varname);
    void SetVariables(const VectorXd& x);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;

    Eigen::VectorXd variable;
    int total_varaible_num;
};

#endif // STATE_VARIABLE_H
