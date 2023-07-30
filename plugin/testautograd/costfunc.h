#ifndef COSTFUNC_H
#define COSTFUNC_H

#include <QObject>
#include "ifopt/cost_term.h"
#include "Eigen/core"
#include "autograd/variablematrix.h"
#include "service/Datalogservice.h"

class costfunc :public ifopt::CostTerm
{
public:
    costfunc();
    double GetCost() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac) const override;
    void FillHessionBlock (std::string var_set, Jacobian& jac,int irow) const override;
    mutable ATtensor m_variable;
    mutable Eigen::MatrixXd eigendata;
    mutable Eigen::MatrixXd Jac;
    mutable ATtensor outcome;
    mutable Datalogservice *m_service;
};

#endif // COSTFUNC_H
