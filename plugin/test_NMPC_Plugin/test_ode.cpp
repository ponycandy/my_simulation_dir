#include "test_ode.h"
#include "math.h"
#include "state_file.h"
test_ODE::test_ODE()
{
    l=1;
    m1=1;
    m2=1;
    g=9.8;
}

Eigen::MatrixXd test_ODE::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    //--------------cartpole问题
    //------------------------控制量1 force 状态量4 phi dphi x dx


        double theta=state_mat(0,0);
        double Dtheta=state_mat(1,0);
        double x=state_mat(2,0);
        double Dx=state_mat(3,0);
        double F=act_mat(0,0);
        double Eigen4[4];
        Eigen::MatrixXd dy;
        dy.resize(4,1);
        dy.setZero();
        state_file(Dtheta,Dx,F,g,l,m1,m2,theta,Eigen4);
        dy=Eigen::Map<Eigen::MatrixXd>(Eigen4,4,1);
        return dy;

    //--------------four legged 问题
    //------------------------控制量12 关节力矩 force 状态量12 x y z vx vy vz alpha beta gama p q r
    //---------------动力学考虑：1.使用RoboDynamics库自动计算各个矩阵（闭形式，拉格朗日方法）
    //-------------------------2.不使用矩阵,自动微分法（牛顿欧拉方法）
    //以上两者都需要动力学库（自己写效率实在太低）

}
