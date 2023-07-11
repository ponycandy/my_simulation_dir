#ifndef CONTROLCONSTRAIN_H
#define CONTROLCONSTRAIN_H

#include "ifopt/constraint_set.h"
#include "PolyParams.h"
#include "include/Autogradient/AutoCalc.h"
class ControlConstrain:public ifopt::ConstraintSet,public AutoCalc
{
public:
    ControlConstrain(int num,std::string &name);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void GetValue(Eigen::VectorXd &x,Eigen::MatrixXd &returnvalue) const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    void FillinG(Eigen::VectorXd &g) const;
    mutable int current_agent_num;
    mutable int dec_num;
    mutable int pointNum;
    mutable int miniRadius;
    mutable double steptime;
    mutable int agentnum;
    mutable PolyParams *m_poly;
    mutable int constrainIndex;
    mutable int consnum;
};

#endif // CONTROLCONSTRAIN_H
