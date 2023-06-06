#ifndef TERMINALSET_H
#define TERMINALSET_H
#include <ifopt/constraint_set.h>

class TerminalSet: public ifopt::ConstraintSet
{
public:
    TerminalSet();
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;

};

#endif // TERMINALSET_H
