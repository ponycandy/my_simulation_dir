#ifndef MINIMIZE_TOPOLOGY_H
#define MINIMIZE_TOPOLOGY_H

#include "ifopt/cost_term.h"
#include "CommonstructAndfunction.h"


class minimize_Topology:public ifopt::CostTerm
{
public:
    minimize_Topology(std::string name);
    double GetCost() const override;
    void FillHessionBlock(std::string var_set, Jacobian& jac_block,int irow) const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac) const override;

    mutable swarmvehicle var_struct;
    mutable int  agentnum;
    mutable double Incp;
    mutable int  decnum;
    mutable double collision_r;
    mutable  Eigen::MatrixXd stateMat;//状态矩阵，尺寸为：state_num*dec_num
    mutable  Eigen::MatrixXd actMat;//控制量矩阵，尺寸为：act_num*dec_num
    mutable Eigen::MatrixXd m_jac;
    QVector<Eigen::Vector2d> Target_Traj;
    mutable Eigen::MatrixXd m_Hession;
};
#endif // MINIMIZE_TOPOLOGY_H
