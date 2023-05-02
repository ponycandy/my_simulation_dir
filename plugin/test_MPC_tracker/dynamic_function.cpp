
#include "dynamic_function.h"
#include "Eigen/Core"
dynamic_function::dynamic_function(QObject *parent)
    : QObject{parent}
{

}

void dynamic_function::get_A_and_B(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat, Eigen::MatrixXd &A_mat, Eigen::MatrixXd &B_mat)
{

    //    double x=state_mat(0,0);
    //    double Dx=state_mat(1,0);
    //    double F=act_mat(0,0);


    A_mat<<0,1,0,0;
    B_mat<<0,1;

}

Eigen::MatrixXd dynamic_function::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    double x=state_mat(0,0);
    double Dx=state_mat(1,0);
    double F=act_mat(0,0);





    Eigen::MatrixXd dy;
    dy.resize(2,1);
    dy.setZero();

    dy<<Dx,F;

    return dy;


}

