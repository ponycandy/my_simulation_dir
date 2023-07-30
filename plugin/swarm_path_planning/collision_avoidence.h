#ifndef COLLISION_AVOIDENCE_H
#define COLLISION_AVOIDENCE_H


#include "ifopt/constraint_set.h"
#include "CommonstructAndfunction.h"
#include "service/Datalogservice.h"
class Collision_Avoidence:public ifopt::ConstraintSet
{
public:
    Collision_Avoidence(int num, std::string name);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    void FillHessionBlock(std::string var_set, Jacobian& jac_block,int irow) const override;
    mutable swarmvehicle var_struct;
    mutable int  agentnum;
    mutable int  decnum;
    mutable double collision_r;
    mutable  Eigen::MatrixXd stateMat;//状态矩阵，尺寸为：state_num*dec_num
    mutable  Eigen::MatrixXd actMat;//控制量矩阵，尺寸为：act_num*dec_num
    mutable Eigen::MatrixXd m_jac;
    mutable int constrainnum;
    mutable Datalogservice *m_service;
};

#endif // COLLISION_AVOIDENCE_H
