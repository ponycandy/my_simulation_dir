#include "testode_jac.h"

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
    dydx.resize(4,5);
    dydx.setZero();

    dydx<<                                              0,                                                                                                                                                                                                                                                                                                                                                                                                              0,                                                                          1, 0, 0,
    -cos(theta)/(- l*m2*cos(theta)*cos(theta) + l*m1 + l*m2), (sin(theta)*(l*m2*sin(theta)*dtheta*dtheta + F))/(- l*m2*cos(theta)*cos(theta) + l*m1 + l*m2) - (g*cos(theta)*(m1 + m2))/(- l*m2*cos(theta)*cos(theta) + l*m1 + l*m2) - (dtheta*dtheta*l*m2*cos(theta)*cos(theta))/(- l*m2*cos(theta)*cos(theta) + l*m1 + l*m2) + (2*l*m2*cos(theta)*cos(theta)*sin(theta)*(l*m2*sin(theta)*dtheta*dtheta + F))/pow(- l*m2*cos(theta)*cos(theta) + l*m1 + l*m2,2) + (2*g*l*m2*cos(theta)*pow(sin(theta),2)*(m1 + m2))/pow(- l*m2*cos(theta)*cos(theta) + l*m1 + l*m2,2), -(2*dtheta*l*m2*cos(theta)*sin(theta))/(- l*m2*cos(theta)*cos(theta) + l*m1 + l*m2), 0, 0,
                                                  0,                                                                                                                                                                                                                                                                                                                                                                                                              0,                                                                          0, 0, 1,
                    1/(- m2*cos(theta)*cos(theta) + m1 + m2),                                                                          (g*m2*cos(theta)*cos(theta))/(- m2*cos(theta)*cos(theta) + m1 + m2) - (g*m2*sin(theta)*sin(theta))/(- m2*cos(theta)*cos(theta) + m1 + m2) + (dtheta*dtheta*l*m2*cos(theta))/(- m2*cos(theta)*cos(theta) + m1 + m2) - (2*g*m2*m2*cos(theta)*cos(theta)*sin(theta)*sin(theta))/pow(- m2*cos(theta)*cos(theta) + m1 + m2,2) - (2*m2*cos(theta)*sin(theta)*(l*m2*sin(theta)*dtheta*dtheta + F))/pow(- m2*cos(theta)*cos(theta) + m1 + m2,2),                   (2*dtheta*l*m2*sin(theta))/(- m2*cos(theta)*cos(theta) + m1 + m2), 0, 0;


    return dydx;
}
