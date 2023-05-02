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
    delta_t=30;
    Amat.resize(2,2);
    Amat.setZero();
    Amat << 0.0, 1.0,
            0.0,0.0;


    Bmat.resize(2,1);
    Bmat.setZero();
    Bmat << 0.0,
            1.0;
    Cmat.resize(2,2);
    Cmat.setZero();
    Cmat << 1.0,0.0,
            0.0,1.0;
    state.resize(2,1);
    state.setZero();
    state << 10.0,
            5.0;
    control_0.resize(1,1);
    control_0.setZero();
    control_0(0,0)=0.1;
    sense_0.resize(2,1);
    sense_0.setZero();

}
void Simulator::randonize_state()
{
}
void Simulator::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
        state=state+delta_t*0.001*(Amat*state+Bmat*control_0(0,0));
}

void Simulator::control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat)
{
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

    emit sig_agent_state_update(vectors);
}
void Simulator::detect_neibor(Eigen::MatrixXd state_mat)
{

}
void Simulator::detect_collision()
{
}
