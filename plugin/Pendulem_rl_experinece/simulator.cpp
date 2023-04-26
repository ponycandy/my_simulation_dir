#include "simulator.h"
#include <QElapsedTimer>
#include <QCoreApplication>
#include "QtDebug"
#include "state_file.h"

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
    Cmat << 0.0,0.0,1.0,0.0,
        1.0,0.0,0.0,0.0;
    state.resize(4,1);
    state << 3.1415926535,
        0.0,
        0.0,
        0.0;
    control_0.resize(1,1);
    control_0(0,0)=0;
    sense_0.resize(2,1);
    sense_0.setZero();

}
void Simulator::randonize_state()
{
}
void Simulator::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    double theta=state(0,0);
    double dtheta=state(1,0);
    double x=state(2,0);
    double dx=state(3,0);
    double F=control_0(0,0);




    double Eigen4[4];
    Eigen::MatrixXd dy;
    dy.resize(4,1);
    dy.setZero();
    state_file(dtheta,dx,F,g,l,m1,m2,theta,Eigen4);
    dy=Eigen::Map<Eigen::MatrixXd>(Eigen4,4,1);

    state=state+0.001*delta_t * dy;


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
