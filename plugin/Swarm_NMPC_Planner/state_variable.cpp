#include "state_variable.h"



State_Variable::State_Variable(int num, std::string &varname):VariableSet(num,varname)
{
    total_varaible_num=num;
    variable.resize(total_varaible_num,1);
    variable.setOnes();
}

void State_Variable::SetVariables(const VectorXd &x)
{
    variable=x;
}

ifopt::Component::VectorXd State_Variable::GetValues() const
{
    Eigen::VectorXd x=variable;
    return x;
}

ifopt::Component::VecBound State_Variable::GetBounds() const
{
    ifopt::Component::VecBound bounds(GetRows());
    for(int k=0;k<total_varaible_num;k++)
    {
        bounds.at(k)=ifopt::NoBound;
    }

    return bounds;
}
