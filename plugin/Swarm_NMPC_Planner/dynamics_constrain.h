#ifndef DYNAMICS_CONSTRAIN_H
#define DYNAMICS_CONSTRAIN_H

#include "ifopt/constraint_set.h"
#include "QVector"
#include <NMPC/NMPC_ODE.h>
#include <NMPC/NMPC_dynamic_Jacob.h>
#include "PolyParams.h"
#include <QMap>
#include <include/MPC/MPC_ODE.h>
typedef Eigen::SparseMatrix<double> Espmat;

class Dynamics_Constrain:public ifopt::ConstraintSet
{
public:
    Dynamics_Constrain(int num);
    VectorXd GetValues() const override;
    void init_num(int state_num,int agent_num,int dec_num,int pointnum,double step) const ;
    VecBound GetBounds() const override;
    void Fill_dynamics_Jacob(Jacobian &jac) const;
    void Fill_dynamics_action(Jacobian &jac)  const;
    void Calc_a_2_pi(Eigen::MatrixXd &mat, Eigen::MatrixXd &pt,int decN,int agentindex) const;
    void Calc_a_2_pt(Eigen::MatrixXd &mat, Eigen::MatrixXd &pt,int decN) const;
    void FillJacobianBlock (std::string var_set, Jacobian& jac_block) const override;
    void FillinG(Eigen::VectorXd &g) const;
    void Copy_Dense_2_Sparse(Jacobian &jac_block,Eigen::MatrixXd mat,int startx,int starty);
    void formactmat() const;
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
    mutable QVector<Eigen::MatrixXd> ActMats;
    mutable Eigen::MatrixXd states;
    mutable QMap<double,int> time_2_phase_map;
    mutable Eigen::MatrixXd dec_2_coef_map;
    mutable Eigen::MatrixXd actMat;
    mutable Eigen::MatrixXd Combined_cons;
    mutable Eigen::MatrixXd A_mat;
    mutable Eigen::MatrixXd B_mat;//4*2矩阵


    mutable Eigen::MatrixXd initstates_of_animals;

    NMPC_ODE *self_ode;
    MPC_ODE *self_jacobian;
    NMPC_Dynamic_Jacob *self_ode_jacob;
};

#endif // DYNAMICS_CONSTRAIN_H
