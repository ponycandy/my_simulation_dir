#include "testcons.h"

testCons::testCons(int num):ConstraintSet(num, "testcons")
{}

void testCons::counts()
{
    member=1;
}

ifopt::Component::VectorXd testCons::GetValues() const
{
    member=0;
    VectorXd g(GetRows());
    Eigen::Vector2d x = GetVariables()->GetComponent("var_set1")->GetValues();
    g(0) = std::pow(x(0),2) + x(1);
    return g;
}

ifopt::Component::VecBound testCons::GetBounds() const
{
    VecBound b(GetRows());
    b.at(0) = ifopt::Bounds(1.0, 1.0);
    return b;
}

void testCons::FillJacobianBlock(std::string var_set, Jacobian &jac_block) const
{
    // must fill only that submatrix of the overall Jacobian that relates
    // to this constraint and "var_set1". even if more constraints or variables
    // classes are added, this submatrix will always start at row 0 and column 0,
    // thereby being independent from the overall problem.
    if (var_set == "var_set1") {
        Eigen::Vector2d x = GetVariables()->GetComponent("var_set1")->GetValues();

        jac_block.coeffRef(0, 0) = 2.0*x(0); // derivative of first constraint w.r.t x0
        jac_block.coeffRef(0, 1) = 1.0;      // derivative of first constraint w.r.t x1
    }
}
