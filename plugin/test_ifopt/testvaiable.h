#ifndef TESTVAIABLE_H
#define TESTVAIABLE_H

#include <ifopt/variable_set.h>
class testVaiable:public ifopt::VariableSet
{
public:
    testVaiable(int num);
    void do_sthing();
    void SetVariables(const VectorXd &x);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
private:
    double x0_, x1_;
};

#endif // TESTVAIABLE_H
