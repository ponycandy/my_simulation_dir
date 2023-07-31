#ifndef OBS_AVOIDENCE_H
#define OBS_AVOIDENCE_H

#include "ifopt/constraint_set.h"
#include "SwarmObstacle.h"
#include "CommonstructAndfunction.h"
#include "service/CollisionDetectservice.h"
#include "service/Datalogservice.h"
class Obs_Avoidence:public ifopt::ConstraintSet
{
public:
    Obs_Avoidence(int num, std::string name);
    double PotentialCalc(double z,double &first,double &second) const ;
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void FillHessionBlock(std::string var_set, Jacobian& jac_block,int irow) const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    void predict_beta_agent() const;
    mutable swarmvehicle var_struct;
    mutable QVector<Eigen::MatrixXd> Hession_Tensor;
    mutable int  agentnum;
    mutable int  decnum;
    mutable double collision_r;
    mutable Eigen::MatrixXd m_Hession;
    mutable  Eigen::MatrixXd stateMat;//状态矩阵，尺寸为：state_num*dec_num
    mutable  Eigen::MatrixXd actMat;//控制量矩阵，尺寸为：act_num*dec_num
    mutable Eigen::MatrixXd m_jac;
    mutable QMap<int,SwarmObstacle*> obsbounding_group;
    mutable CollisionDetectservice *m_service;
    mutable int obs_num;
    mutable int constrainnum;
    mutable double communication_range;
 mutable double maximumPotential;
    mutable Datalogservice *m_servicex;
};

#endif // OBS_AVOIDENCE_H
