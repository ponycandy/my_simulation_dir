#ifndef TEST_ODE_H
#define TEST_ODE_H

#include "include/NMPC/NMPC_ODE.h"
#include "Eigen/Core"
class test_ODE:public NMPC_ODE
{
public:
    test_ODE();
    Eigen::MatrixXd ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat) override;

    double l;
    double m1;
    double m2;
    double g;
};

#endif // TEST_ODE_H
