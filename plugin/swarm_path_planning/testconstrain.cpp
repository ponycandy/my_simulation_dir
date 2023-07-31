#include "testconstrain.h"

TestConstrain::TestConstrain(int num):ifopt::ConstraintSet(num,"TestConstrain")
{
    constrainnum=num;
}

ifopt::Component::VectorXd TestConstrain::GetValues() const
{
    VectorXd g(GetRows());
    g.setConstant(-2);
    return g;
}

ifopt::Component::VecBound TestConstrain::GetBounds() const
{
    VecBound b(GetRows());

    for(int i=1;i<=constrainnum;i++)
    {
        b.at(i-1)=ifopt::BoundSmallerZero;
    }

    return b;
}

void TestConstrain::FillHessionBlock(std::string var_set, Jacobian &jac_block, int irow) const
{
    jac_block.setZero();
}

void TestConstrain::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    jac_block.setZero();

}
