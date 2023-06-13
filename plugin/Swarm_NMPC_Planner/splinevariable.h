#ifndef SPLINEVARIABLE_H
#define SPLINEVARIABLE_H

#include <ifopt/variable_set.h>
#include <Eigen/Core>
class SplineVariable:public ifopt::VariableSet
{
public:
    SplineVariable(int num ,std::string& varname);
    void SetVariables(const VectorXd& x);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;

    Eigen::VectorXd variable;
    int var_num;
    int pointnum;
    int dims;
    int dec_num;
    double steptime;
};

#endif // SPLINEVARIABLE_H
