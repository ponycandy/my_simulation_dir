#ifndef TESTODE_JAC_H
#define TESTODE_JAC_H

#include "Eigen/Core"
#include "include/NMPC/NMPC_dynamic_Jacob.h"
class testODE_jac:public NMPC_Dynamic_Jacob
{
public:
    testODE_jac();
    Eigen::MatrixXd jacobica(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat) override;
    double l;
    double m1;
    double m2;
    double g;


};

#endif // TESTODE_JAC_H
