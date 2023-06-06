#ifndef EXTRACONSTRAIN_H
#define EXTRACONSTRAIN_H

#include <ifopt/constraint_set.h>
class extraconstrain : public ifopt::ConstraintSet {
public:
    extraconstrain() : extraconstrain("constraint2") {}

    // This constraint set just contains 1 constraint, however generally
    // each set can contain multiple related constraints.
    extraconstrain(const std::string& name) : ConstraintSet(1, name) {}

    // The constraint value minus the constant value "1", moved to bounds.
    VectorXd GetValues() const override
    {
        VectorXd g(GetRows());
        Eigen::Vector2d x = GetVariables()->GetComponent("var_set1")->GetValues();
        g(0) = x(1);
        return g;
    };

    // The only constraint in this set is an equality constraint to 1.
    // Constant values should always be put into GetBounds(), not GetValues().
    // For inequality constraints (<,>), use Bounds(x, inf) or Bounds(-inf, x).
    VecBound GetBounds() const override
    {
        VecBound b(GetRows());
        b.at(0) = ifopt::NoBound;
        return b;
    }

    // This function provides the first derivative of the constraints.
    // In case this is too difficult to write, you can also tell the solvers to
    // approximate the derivatives by finite differences and not overwrite this
    // function, e.g. in ipopt.cc::use_jacobian_approximation_ = true
    // Attention: see the parent class function for important information on sparsity pattern.
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override
    {
        // must fill only that submatrix of the overall Jacobian that relates
        // to this constraint and "var_set1". even if more constraints or variables
        // classes are added, this submatrix will always start at row 0 and column 0,
        // thereby being independent from the overall problem.
        if (var_set == "var_set1") {
            Eigen::Vector2d x = GetVariables()->GetComponent("var_set1")->GetValues();
            jac_block.coeffRef(0, 1) = 1.0;      // derivative of first constraint w.r.t x1
        }
    }
};
#endif // EXTRACONSTRAIN_H
