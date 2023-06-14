#include "jacobian_state.h"

Jacobian_state::Jacobian_state()
{

}

Eigen::MatrixXd Jacobian_state::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    Eigen::MatrixXd dstate;
    dstate.resize(4,1);
    dstate<<0,0,act_mat(0,0),act_mat(1,0);
    return dstate;
}

void Jacobian_state::get_A_and_B(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat, Eigen::MatrixXd &A_mat, Eigen::MatrixXd &B_mat)
{
    A_mat<<0,0,1,0,
    0,0,0,1,
    0,0,0,0,
        0,0,0,0;
    B_mat<<0,0,
            0,0,
            1,0,
        0,1;
}
