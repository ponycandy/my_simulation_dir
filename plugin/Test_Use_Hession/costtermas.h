#ifndef COSTTERMAS_H
#define COSTTERMAS_H

#include "ifopt/cost_term.h"
class CostTermas:public ifopt::CostTerm
{
public:
    CostTermas(std::string name );
    double GetCost() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac) const override;
    void FillHessionBlock(std::string var_set, Jacobian& jac_block,int irow) const override;
};

#endif // COSTTERMAS_H
