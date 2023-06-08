#include "dynamics_of_animals.h"

Dynamics_of_Animals::Dynamics_of_Animals()
{

}

Eigen::MatrixXd Dynamics_of_Animals::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{

    Eigen::MatrixXd dy;
    dy.resize(4,1);
    dy.setZero();
    dy<<state_mat(0,0),state_mat(1,0),act_mat(0,0),act_mat(1,0);
    return dy;
}
