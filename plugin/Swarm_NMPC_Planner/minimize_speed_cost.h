#ifndef MINIMIZE_SPEED_COST_H
#define MINIMIZE_SPEED_COST_H

#include "ifopt/cost_term.h"
#include "QVector"
#include "PolyParams.h"
#include "Eigen/Core"

class Minimize_Speed_Cost:public ifopt::CostTerm
{
public:
    Minimize_Speed_Cost();
    double GetCost() const override;
    void FillJacobianBlock (std::string var_set, Jacobian& jac) const override;
    void init_num(int state_num, int agent_num, int dec_num, int pointnum,double step) const;
    mutable double coef_K;
    mutable double constrainnum;
    mutable int statenum;
    mutable int agentnum;
    mutable int actnum;
    mutable int dims;
    mutable int pointnum;
    mutable int decnum;
    mutable int current_agent;
    mutable double steptime;
    mutable QVector<PolyParams> m_polys;
    mutable QVector<Eigen::MatrixXd> single_spline_jacob;
    mutable QVector<Eigen::MatrixXd> ActMats;
    mutable QVector<Jac_Group> Jac_Group_vactor;
    mutable Eigen::MatrixXd states;
    mutable QMap<double,int> time_2_phase_map;
    mutable Eigen::MatrixXd dec_2_coef_map;
    mutable Eigen::MatrixXd actMat;
    mutable Eigen::MatrixXd Combined_cons;
    mutable Eigen::MatrixXd A_mat;
    mutable Eigen::MatrixXd B_mat;//4*2矩阵
    mutable double distance;
    mutable Jac_Group jgroup;
    mutable Eigen::MatrixXd D2statemat;
    mutable double epson;


    mutable Eigen::MatrixXd initstates_of_animals;
};

#endif // MINIMIZE_SPEED_COST_H
