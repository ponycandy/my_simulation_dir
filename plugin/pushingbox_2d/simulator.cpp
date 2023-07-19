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


void Simulator::init()

{
    delta_t=30;
    Amat.resize(4,4);
    Amat.setZero();
    Amat << 0.0, 1.0,0,0,
            0.0,0.0,0,0 ,
            0,0,0,1,
            0,0,0,0;


    Bmat.resize(4,2);
    Bmat.setZero();
    Bmat << 0.0,0.0,
            1.0,0.0,
            0,0.0,
            0.0,1.0;
    Cmat.resize(4,4);
    Cmat.setZero();
    Cmat.setIdentity();
    state.resize(4,1);
    state.setZero();
    state << 1.0,
            0.0,1,0;
    control_0.resize(2,1);
    control_0.setZero();
    control_0(0,0)=0.1;
    control_0(1,0)=0.1;
    sense_0.resize(4,1);
    sense_0.setZero();

}
void Simulator::randonize_state()
{
}
void Simulator::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
        state=state+delta_t*0.001*(Amat*state+Bmat*control_0);
}

void Simulator::control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat)
{
//        control_0(0,0)=-state(0,0)-state(1,0);
//         control_0(1,0)=-state(2,0)-state(3,0);
}
void Simulator::sensor(Eigen::MatrixXd state_mat)
{
    sense_0=Cmat*state;
}

void Simulator::broad_cast(Eigen::MatrixXd state_mat, Eigen::MatrixXd act_mat, Eigen::MatrixXd sensor)
{

    QVector<double> vectors;
    vectors.insert(0,sense_0(0,0));
    vectors.insert(1,sense_0(2,0));

    emit sig_agent_state_update(vectors);
}
void Simulator::detect_neibor(Eigen::MatrixXd state_mat)
{

}
void Simulator::detect_collision()
{
}
