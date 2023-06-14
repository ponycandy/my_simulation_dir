#ifndef TESTPOLYPARAMS_H
#define TESTPOLYPARAMS_H

#include "ifopt/constraint_set.h"
#include "PolyParams.h"
class TestPolyParams:public ifopt::ConstraintSet
{
public:
    TestPolyParams(int num);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
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
    mutable Eigen::MatrixXd actmat;
};

#endif // TESTPOLYPARAMS_H
