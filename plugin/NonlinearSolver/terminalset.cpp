#include "terminalset.h"

TerminalSet::TerminalSet():ConstraintSet(4, "Terminal_constrain")
{

}

ifopt::Component::VectorXd TerminalSet::GetValues() const
{
    VectorXd target(4);
    target<<3.1415926535,0,0,0;
    VectorXd g(GetRows());//获取约束的个数，也就是行数
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    int totalsize=x.cols();
    for(int i=0;i<=3;i++)
    {
        g(3-i)=x(totalsize-1-i)-target(3-i);
    }
    return g;
}

ifopt::Component::VecBound TerminalSet::GetBounds() const
{
    VecBound b(GetRows());

    for(int i=1;i<=4;i++)
    {
        b.at(i-1)=ifopt::Bounds(0.0, 0.0);
    }

    return b;
}

void TerminalSet::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    if (var_set == "action_state_set1")
    {
        for(int i=0;i<=3;i++)
        {
            jac_block.coeffRef(i,i)=1;
        }
    }

}
