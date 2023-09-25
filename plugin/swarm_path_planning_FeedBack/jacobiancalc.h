#ifndef JACOBIANCALC_H
#define JACOBIANCALC_H

#include "include/NMPC/NMPC_dynamic_Jacob.h"
class Jacobiancalc:public NMPC_Dynamic_Jacob
{
public:
    Jacobiancalc();
    Eigen::MatrixXd jacobica(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat) override;
    void Hession(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat,Eigen::MatrixXd &Hession_temp,int state_index) override;
    int agent_Num;
    Eigen::MatrixXd returnmat;
    Eigen::MatrixXd JacBlock;

};

#endif // JACOBIANCALC_H
