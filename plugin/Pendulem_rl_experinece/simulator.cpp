#include "simulator.h"
#include <QElapsedTimer>
#include <QCoreApplication>
#include "QtDebug"
Simulator::Simulator(QObject *parent)
{

}

void Simulator::randonize_obs()
{

}

void Simulator::update_obs()
{

}

double Simulator::get_angle(double vx, double vy)
{
    double value=0;
    if(vx==0 && vy==0)
    {
        return value;
    }
    else
    {
        value=atan2(vy,vx);
        return  value;
    }
}

void Simulator::init()

{
    m1=1;
    m2=1;
    l=1;
    g=9.8;
    delta_t=30;


    Amat.resize(4,4);
    Amat.setZero();
    Amat << 0.0, 1.0, 0.0, 0.0,
        0.0,0.0, 0.0, 0.0,

        0.0, 0.0, 0.0, 1.0,
        0.0, 0.0, 0.0, 0.0;
    Bmat.resize(4,1);
    Bmat << 0.0,
        0.0,
        0.0,
        0.0;
    Cmat.resize(2,4);
    Cmat << 1.0,0.0,0.0,0.0,
        0.0,0.0,1.0,0.0;
    state.resize(4,1);
    state << 0.0,
        0.0,
        2.5,
        0.0;
    control_0.resize(1,1);
    control_0(0,0)=4;
    sense_0.resize(2,1);
    sense_0.setZero();

}
void Simulator::randonize_state()
{
}
void Simulator::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    //  state的依次顺序是：x  dx  theta dtherta
    double x=state(0,0);
    double dx=state(1,0);
    double theta=state(2,0);
    double dtheta=state(3,0);

    double F=control_0(0,0);

    double cosTheta = cos(theta);
    double sinTheta = sinTheta;

    Eigen::MatrixXd dy;
    dy.resize(4,1);
    dy.setZero();
    dy(2,0)=dtheta;
    dy(3,0)=- (cosTheta*(l*m2*sinTheta*dtheta*dtheta + F))/(- l*m2*cosTheta*cosTheta + l*m1 + l*m2)
               - (g*sinTheta*(m1 + m2))/(- l*m2*cosTheta*cosTheta + l*m1 + l*m2);
    dy(0,0)=dx;
    dy(1,0)=  (l*m2*sinTheta*dtheta*dtheta + F)/
                   (- m2*cosTheta*cosTheta + m1 + m2) + (g*m2*cosTheta*sinTheta)/(- m2*cosTheta*cosTheta + m1 + m2);


    x = x + 0.001*delta_t * dy(0,0);//
    dx = dx + 0.001*delta_t * dy(1,0);//

    theta= theta + 0.001*delta_t * dy(2,0);
    dtheta = dtheta + 0.001*delta_t * dy(3,0);
    if(theta>2*3.1415926535)
    {
        theta=theta-2*3.1415926535;
    }
    if(theta<-2*3.1415926535)
    {
        theta=theta+2*3.1415926535;
    }

    state(0,0)=x;
    state(1,0)=dx;
    state(2,0)=theta;
    state(3,0)=dtheta;


}

void Simulator::control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat)
{
    //    control_0(0,0)= -control_0(0,0);
}
void Simulator::sensor(Eigen::MatrixXd state_mat)
{
    sense_0=Cmat*state;
}

void Simulator::broad_cast(Eigen::MatrixXd state_mat, Eigen::MatrixXd act_mat, Eigen::MatrixXd sensor)
{
    //    x_pos=state_array[0];
    //     omega=state_array[1];
    //     penlength=state_array[2];
    //     cartwidth=state_array[3];
    //     cartheight=state_array[4];
    //     pendwidth=state_array[5];
    //     vel=state_array[6];
    //     phi=state_array[7];
    QVector<double> vectors;
    vectors.insert(0,sense_0(0,0));
    vectors.insert(1,0);
    vectors.insert(2,10);
    vectors.insert(3,3);
    vectors.insert(4,3);
    vectors.insert(5,0.2);
    vectors.insert(6,0);
    vectors.insert(7,sense_0(1,0));

    emit sig_agent_state_update(vectors);
}
void Simulator::detect_neibor(Eigen::MatrixXd state_mat)
{

}
void Simulator::detect_collision()
{
}
