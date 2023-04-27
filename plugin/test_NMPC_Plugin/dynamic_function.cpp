
#include "dynamic_function.h"
#include "myfile.h"
#include "state_file.h"
#include "Eigen/Core"
dynamic_function::dynamic_function(QObject *parent)
    : QObject{parent}
{
    g=9.8;
    l=1;
    m1=1;
    m2=1;
}

void dynamic_function::get_A_and_B(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat, Eigen::MatrixXd &A_mat, Eigen::MatrixXd &B_mat)
{
    double theta=state_mat(0,0);
    double Dtheta=state_mat(1,0);

    double x=state_mat(2,0);
    double Dx=state_mat(3,0);
    double F=act_mat(0,0);
    double jacmat_array[20];

    Eigen::MatrixXd jac_mat;
    myfile(Dtheta,F,g,l,m1,m2,theta,jacmat_array);
    jac_mat=Eigen::Map<Eigen::MatrixXd>(jacmat_array,4,5);
    A_mat=jac_mat.block(0,1,4,4);
    B_mat=jac_mat.block(0,0,4,1);


    //    double x=state_mat(0,0);
    //    double vx=act_mat(0,0);
    //    A_mat<<0;
    //    B_mat<<1;

}

Eigen::MatrixXd dynamic_function::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    return act_mat;

}

