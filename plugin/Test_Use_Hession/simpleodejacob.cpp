#include "simpleodejacob.h"

simpleodejacob::simpleodejacob()
{

}

Eigen::MatrixXd simpleodejacob::jacobica(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    Eigen::MatrixXd jac;
    jac.resize(2,3);
    jac<<0,0,3*state_mat(1,0)*state_mat(1,0),
        1,0,0;
    return jac;
}

void simpleodejacob::Hession(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat, Eigen::MatrixXd &Hession_temp, int state_index)
{
    if(state_index==0)
    {
//        Hession_temp.setZero();
        Hession_temp(2,2)=6*state_mat(1,0);
    }
    else
    {
        Hession_temp.setZero();
    }
    //无法复现......
    //但是问题感觉始终存在，不爽....
}
