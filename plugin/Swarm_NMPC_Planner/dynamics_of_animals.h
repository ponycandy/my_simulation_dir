#ifndef DYNAMICS_OF_ANIMALS_H
#define DYNAMICS_OF_ANIMALS_H

#include "include/NMPC/NMPC_ODE.h"
#include "Eigen/Core"
class Dynamics_of_Animals:public NMPC_ODE
{
public:
    Dynamics_of_Animals();
    Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
        override;

};

#endif // DYNAMICS_OF_ANIMALS_H
