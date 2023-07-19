#ifndef COSTFUNC_H
#define COSTFUNC_H

#include <QObject>
#include "ifopt/cost_term.h"
#include "Eigen/core"
#include "autograd/variablematrix.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
class costfunc :public ifopt::CostTerm
{
public:
    costfunc();
    double GetCost() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac) const override;
    mutable ATtensor m_variable;
    mutable Eigen::MatrixXd eigendata;
    mutable Eigen::MatrixXd Jac;
    mutable ATtensor outcome;
};

#endif // COSTFUNC_H
