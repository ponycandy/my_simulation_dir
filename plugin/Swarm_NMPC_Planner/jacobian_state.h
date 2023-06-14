#ifndef JACOBIAN_STATE_H
#define JACOBIAN_STATE_H

#include <include/MPC/MPC_ODE.h>
class Jacobian_state:public MPC_ODE
{
public:
    Jacobian_state();
    Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat) override;
    void get_A_and_B(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat, Eigen::MatrixXd &A_mat, Eigen::MatrixXd &B_mat) override ;
    int agentnum;
    double coefK;
    double f_norm;
};

#endif // JACOBIAN_STATE_H
