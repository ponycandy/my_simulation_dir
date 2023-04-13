﻿#include "test_ode.h"
#include "math.h"
test_ODE::test_ODE()
{
    l=1;
    m1=1;
    m2=1;
    g=9.8;
}

Eigen::MatrixXd test_ODE::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    //cartpole问题
    //控制量1 force 状态量4 phi dphi x dx
    //

    double theta=state_mat(0,0);
    double dtheta=state_mat(1,0);
    double x=state_mat(2,0);
    double dx=state_mat(3,0);
    double F=act_mat(0,0);

    Eigen::MatrixXd dy;
    dy.resize(4,1);
    dy.setZero();
    dy(0,0)=dtheta;
    dy(1,0)=- (cos(theta)*(l*m2*sin(theta)*dtheta*dtheta + F))/(- l*m2*cos(theta)*cos(theta) + l*m1 + l*m2)
            - (g*sin(theta)*(m1 + m2))/(- l*m2*cos(theta)*cos(theta) + l*m1 + l*m2);
    dy(2,0)=dx;
    dy(3,0)=  (l*m2*sin(theta)*dtheta*dtheta + F)/
            (- m2*cos(theta)*cos(theta) + m1 + m2) + (g*m2*cos(theta)*sin(theta))/(- m2*cos(theta)*cos(theta) + m1 + m2);
    return dy;

}
