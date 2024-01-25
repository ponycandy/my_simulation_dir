
#include "simulator.h"

#include "QtDebug"
#include "Vehicle_simulatorActivator.h"
Simulator::Simulator(QObject *parent)
{
    Statemat.resize(7,1);
    Statemat.setZero();
    Statemat<<10,0,0,0,0,0,0;
    feedbackstate.resize(6,1);
    feedbackstate.setZero();
    feedbackstate<<Statemat(0,0),Statemat(1,0),Statemat(2,0),
        Statemat(3,0),Statemat(4,0),Statemat(5,0);

    posstate.resize(3,1);
    posstate.setZero();

}

double Simulator::roadmodel(double s)
{
    //return 0;//测试直线
    //测试和matlab一致的弯道
    if(s<30)
    {
        return 0;
    }
    else if(s>=30 && s<=70)
    {
        return 0.125;
    }
    else
    {
        return 0;
    }
}

void Simulator::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{

    int i = 0;
    double v = Statemat(i);i = i + 1;
    double beta = Statemat(i);i = i + 1;
    double omega = Statemat(i);i = i + 1;
    double a_x = Statemat(i);i = i + 1;


    double e=Statemat(i);i = i + 1;//e是横向误差
    double s=Statemat(i);i = i + 1;//s是曲率坐标系长度
    double erro_PHI=Statemat(i);i = i + 1;//是航向误差

    double curv=0;
    //从s计算curv
    curv=roadmodel(s);
    double x_pos=posstate(0,0);
    double y_pos=posstate(1,0);
    double phi=posstate(2,0);

    double Dx=v*cos(phi+beta);
    double Dy=v*sin(phi+beta);
    double Dphi=omega;
    Eigen::MatrixXd  Dposstate;
    Dposstate.resize(3,1);
    Dposstate<<Dx,Dy,Dphi;
    //
    double F_z_f = mass/l_x*(l_r*g - h_cg*a_x);
    double F_z_r = mass/l_x*(l_f*g + h_cg*a_x);


    double omega_r=controlmat(2);
    double omega_f=controlmat(1);
    double delta=controlmat(0);


    double  v_x_f_center = v*cos(beta - delta) + omega*l_f*sin(delta);
    double  v_x_f_slip = omega_f*R_wheel - v_x_f_center;
    double  v_y_f_slip = -v*sin(beta - delta) - omega*l_f*cos(delta);
    double  v_f_slip = sqrt(v_x_f_slip*v_x_f_slip + v_y_f_slip*v_y_f_slip) + 1e-4;

    double      v_x_r_center = v*cos(beta);
    double   v_x_r_slip = omega_r*R_wheel - v_x_r_center;
    double  v_y_r_slip = -v*sin(beta) + omega*l_r;
    double v_r_slip = sqrt(v_x_r_slip*v_x_r_slip + v_y_r_slip*v_y_r_slip) + 1e-4;

    double s_f = v_f_slip/(omega_f*R_wheel + 1e-4) + 1e-4;
    double s_r = v_r_slip/(omega_r*R_wheel + 1e-4) + 1e-4;


    double Mu_f = D*sin(C*atan(s_f*B - E*(s_f*B - atan(s_f*B))));
    double  Mu_r = D*sin(C*atan(s_r*B - E*(s_r*B - atan(s_r*B))));

    double Mu_x_f = Mu_f*v_x_f_slip/v_f_slip;
    double Mu_x_r = Mu_r*v_x_r_slip/v_r_slip;

    Mu_f = D*sin(C*atan(s_f*B - E*(s_f*B - atan(s_f*B))));
    Mu_r = D*sin(C*atan(s_r*B - E*(s_r*B - atan(s_r*B))));

    double Mu_y_f = Mu_f*v_y_f_slip/v_f_slip;
    double Mu_y_r = Mu_r*v_y_r_slip/v_r_slip;

    double  F_x_f = Mu_x_f*F_z_f;
    double F_y_f = Mu_y_f*F_z_f;

    double F_x_r = Mu_x_r*F_z_r;
    double F_y_r = Mu_y_r*F_z_r;

    double D_v = 1/mass*(F_x_f*cos(beta - delta) + F_y_f*sin(beta - delta) + F_x_r*cos(beta) + F_y_r*sin(beta));
    double D_beta = 1/(mass*v + 1e-4)*(F_x_f*sin(delta - beta) + F_y_f*cos(delta - beta) + F_y_r*cos(beta) - F_x_r*sin(beta)) - omega;
    double D_omega = 1/inertial_z*((F_x_f*sin(delta) + F_y_f*cos(delta))*l_f - F_y_r*l_r);

    double   v_y = v*sin(beta);
    double D_v_x = 1/mass*(F_x_f*cos(delta) - F_y_f*sin(delta) + F_x_r) + v_y*omega;
    double a_x_0 = D_v_x - v_y*omega;
    double D_a_x = (a_x_0 - a_x)/tau;


    double D_e = v*sin(erro_PHI);
    double D_s = v*cos(erro_PHI)/(1 - curv*e);
    double D_erro_PHI = D_beta + omega - curv*D_s;


    Eigen::MatrixXd D_X ;
    D_X.resize(7,1);
    D_X<<D_v,D_beta,D_omega,D_a_x,D_e,D_s,D_erro_PHI;
//v:1~20 //单位化
    //beta:-0.7~+0.7
    //omega:-1~1
    //a_x:-6~6  //单位化
    //e:-1.5~1.5  //如果e超出了一定范围，就终止了
    //s:0~100  //不作为终止条件，单位化
    //erro_PHI:-0.7~+0.7
    Statemat=Statemat+delta_t*D_X;//ms
    posstate=posstate+delta_t*Dposstate;

    feedbackstate<<Statemat(0,0),Statemat(1,0),Statemat(2,0),
        Statemat(3,0),Statemat(4,0),Statemat(5,0);
    //释放信号

    Eigen::MatrixXd state;
    emit sig_updatepos(posstate);

}

void Simulator::control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat)
{


}
void Simulator::sensor(Eigen::MatrixXd state_mat)
{

}

void Simulator::broad_cast(Eigen::MatrixXd state_mat, Eigen::MatrixXd act_mat, Eigen::MatrixXd sensor)
{

}
