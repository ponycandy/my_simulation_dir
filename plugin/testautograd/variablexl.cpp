#include "variablexl.h"


variablexl::variablexl(int num ):ifopt::VariableSet(num,"x_value_all")
{
    data.resize(num);
    data.setOnes();
}

void variablexl::SetVariables(const VectorXd &x)
{
    data=x;
}

ifopt::Component::VectorXd variablexl::GetValues() const
{
    return data;
}

ifopt::Component::VecBound variablexl::GetBounds() const
{
    ifopt::Component::VecBound bounds(GetRows());
    int num=data.rows();
    for(int k=0;k<num;k++)
    {
        bounds.at(k)=ifopt::NoBound;
    }

    return bounds;
}
