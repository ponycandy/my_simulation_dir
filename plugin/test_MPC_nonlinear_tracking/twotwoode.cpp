
#include "twotwoode.h"

twotwoode::twotwoode(QObject *parent)
    : QObject{parent}
{
    state.resize(1,1);
    state.setZero();
    control_0.resize(1,1);
    control_0.setZero();
    state<<5;
    control_0<<0;

}

Eigen::MatrixXd twotwoode::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    Eigen::MatrixXd dy;
    dy.resize(1,1);
    dy<<act_mat(0,0)*act_mat(0,0)*act_mat(0,0);
    return dy;
}

Eigen::MatrixXd twotwoode::stepin()
{
    state(0,0)=state(0,0)+0.03*control_0(0,0)*control_0(0,0)*control_0(0,0);

    return state;
}

void twotwoode::get_A_and_B(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat, Eigen::MatrixXd &A_mat, Eigen::MatrixXd &B_mat)
{
    A_mat<<0;
    B_mat<<3*act_mat(0,0)*act_mat(0,0);
}


void twotwoode::sensor(Eigen::MatrixXd state_mat)
{
    //do nothing
}

void twotwoode::control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat)
{
    //do nothing
}

void twotwoode::broad_cast(Eigen::MatrixXd state_mat, Eigen::MatrixXd act_mat, Eigen::MatrixXd sensor)
{
//do nothing
}

