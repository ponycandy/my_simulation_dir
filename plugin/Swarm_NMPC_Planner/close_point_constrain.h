#ifndef CLOSE_POINT_CONSTRAIN_H
#define CLOSE_POINT_CONSTRAIN_H
#include "ifopt/constraint_set.h"

class close_point_constrain:public ifopt::ConstraintSet
{
public:
    close_point_constrain(int consNum);
    VectorXd GetValues() const override;
    void init_num(int state_num,int agent_num,int dec_num) const ;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;

    mutable double consta;
    mutable int statenum;
    mutable int agentnum;
    mutable int decnum;
    mutable Eigen::MatrixXd posset;
};

#endif // CLOSE_POINT_CONSTRAIN_H
