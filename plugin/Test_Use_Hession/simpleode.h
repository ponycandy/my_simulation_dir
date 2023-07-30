#ifndef SIMPLEODE_H
#define SIMPLEODE_H
#include <include/NMPC/NMPC_ODE.h>

class simpleode:public NMPC_ODE
{
public:
    simpleode();
    Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat) override;

};

#endif // SIMPLEODE_H
