#ifndef TOPOLOGY_CONSTRAIN_H
#define TOPOLOGY_CONSTRAIN_H

#include "ifopt/constraint_set.h"
#include "CommonstructAndfunction.h"
class Topology_Constrain:public ifopt::ConstraintSet
{
public:
    Topology_Constrain(int num,std::string name);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    mutable swarmvehicle var_struct;
    mutable int  agentnum;
    mutable int  decnum;
    mutable double collision_r;
    mutable  Eigen::MatrixXd stateMat;//状态矩阵，尺寸为：state_num*dec_num
    mutable  Eigen::MatrixXd actMat;//控制量矩阵，尺寸为：act_num*dec_num
    mutable Eigen::MatrixXd m_jac;
    mutable int constrainnum;

};

#endif // TOPOLOGY_CONSTRAIN_H
