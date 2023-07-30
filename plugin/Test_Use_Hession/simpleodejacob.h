#ifndef SIMPLEODEJACOB_H
#define SIMPLEODEJACOB_H

#include "include/NMPC/NMPC_dynamic_Jacob.h"
class simpleodejacob:public NMPC_Dynamic_Jacob
{
public:
    simpleodejacob();
    Eigen::MatrixXd jacobica(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat) override;
    void Hession(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat,Eigen::MatrixXd &Hession_temp,int state_index) override;

};

#endif // SIMPLEODEJACOB_H
