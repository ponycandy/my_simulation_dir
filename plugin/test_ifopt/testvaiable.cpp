#include "testvaiable.h"

testVaiable::testVaiable(int num): VariableSet(num, "var_set1")
{
    //必须在初始化的时候调用父类
    x0_ = 3.5;
    x1_ = 1.5;
}

void testVaiable::do_sthing()
{

}

void testVaiable::SetVariables(const VectorXd &x)
{
    x0_ = x(0);
    x1_ = x(1);
}

ifopt::Component::VectorXd testVaiable::GetValues() const
{
    return Eigen::Vector2d(x0_, x1_);
}

ifopt::Component::VecBound testVaiable::GetBounds() const
{
    VecBound bounds(GetRows());
    bounds.at(0) = ifopt::Bounds(-1.0, 1.0);
    bounds.at(1) = ifopt::NoBound;
    return bounds;
}
