#include "simpleode.h"

simpleode::simpleode()
{

}

Eigen::MatrixXd simpleode::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    Eigen::MatrixXd dstate;
    dstate.resize(2,1);
    dstate(0,0)=pow(state_mat(1,0),3);
    dstate(1,0)=act_mat(0,0);

    return dstate;
}
