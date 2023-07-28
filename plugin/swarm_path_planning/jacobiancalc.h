#ifndef JACOBIANCALC_H
#define JACOBIANCALC_H

#include "include/MPC/NMPC_dynamic_Jacob.h"
class Jacobiancalc:public NMPC_Dynamic_Jacob
{
public:
    Jacobiancalc();
    Eigen::MatrixXd jacobica(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat) override;
    int agent_Num;
};

#endif // JACOBIANCALC_H
