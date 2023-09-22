#ifndef MINIMIZE_TOPOLOGY_H
#define MINIMIZE_TOPOLOGY_H

#include "ifopt/cost_term.h"
#include "CommonstructAndfunction.h"
#include "SwarmObstacle.h"

class minimize_Topology:public ifopt::CostTerm
{
public:
    minimize_Topology(std::string name);
    double GetCost() const override;
    void get_predicted_value(int OBSID,Eigen::MatrixXd &predictMat) const;
    void FillHessionBlock(std::string var_set, Jacobian& jac_block,int irow) const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac) const override;
    int obs_num;
    mutable swarmvehicle var_struct;
    mutable Eigen::MatrixXd relationMatrix;
    mutable Eigen::MatrixXd PredictMat;
    mutable Eigen::MatrixXd SurPredictMat;
    mutable int  agentnum;
    mutable int TriggerSur;
    mutable Eigen::Vector2d obspos;
    mutable double communication_range;
    mutable double Incp;
    mutable int  decnum;
    mutable int selfID;
    mutable int totalNum;
    mutable double collision_r;
    mutable  Eigen::MatrixXd stateMat;//状态矩阵，尺寸为：state_num*dec_num
    mutable  Eigen::MatrixXd actMat;//控制量矩阵，尺寸为：act_num*dec_num
    mutable Eigen::MatrixXd m_jac;
    QVector<Eigen::Vector2d> Target_Traj;
    mutable Eigen::MatrixXd selfinitstate;
    QMap<int,edge*> Edg;
    mutable Eigen::MatrixXd m_Hession;
    mutable Eigen::MatrixXd ObstripR;
};
#endif // MINIMIZE_TOPOLOGY_H
