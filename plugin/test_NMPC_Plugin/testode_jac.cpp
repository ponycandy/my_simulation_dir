#include "testode_jac.h"
#include "myfile.h"
testODE_jac::testODE_jac()
{
    l=1;
    m1=1;
    m2=1;
    g=9.8;
}

Eigen::MatrixXd testODE_jac::jacobica(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    Eigen::MatrixXd dydx;
    //说明：是dy对y和x的的一阶到，也就是左端表头为dy上端表头为控制量+状态量
    double theta=state_mat(0,0);
    double dtheta=state_mat(1,0);
    double x=state_mat(2,0);
    double dx=state_mat(3,0);
    double F=act_mat(0,0);
    double Eigen20[20];
    myfile(dtheta,F,g,l,m1,m2,theta,Eigen20);
    dydx.resize(4,5);
    dydx=Eigen::Map<Eigen::MatrixXd>(Eigen20,4,5);
    return dydx;
}
