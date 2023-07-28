#ifndef OBS_AVOIDENCE_H
#define OBS_AVOIDENCE_H

#include "ifopt/constraint_set.h"
#include "SwarmObstacle.h"
#include "CommonstructAndfunction.h"
#include "service/CollisionDetectservice.h"
class Obs_Avoidence:public ifopt::ConstraintSet
{
public:
    Obs_Avoidence(int num, std::string name);
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    void predict_beta_agent() const;
    mutable swarmvehicle var_struct;
    mutable int  agentnum;
    mutable int  decnum;
    mutable double collision_r;
    mutable  Eigen::MatrixXd stateMat;//状态矩阵，尺寸为：state_num*dec_num
    mutable  Eigen::MatrixXd actMat;//控制量矩阵，尺寸为：act_num*dec_num
    mutable Eigen::MatrixXd m_jac;
    mutable QMap<int,SwarmObstacle*> obsbounding_group;
    mutable CollisionDetectservice *m_service;
    mutable int obs_num;
    mutable int constrainnum;

};

#endif // OBS_AVOIDENCE_H
