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
    I_0=1;
    m_0=2;
    l_0=3;
    b_0=4;
    M_0=10;
    g_0=9.8;
    delta_t=30;
    double mid1=-(I_0+m_0*l_0*l_0)*b_0/(I_0*(m_0+M_0)+M_0*m_0*l_0*l_0);
    double mid2=(g_0*m_0*m_0*l_0*l_0)/(I_0*(m_0+M_0)+M_0*m_0*l_0*l_0);
    double mid3=-(m_0*l_0*b_0)/(I_0*(m_0+M_0)+M_0*m_0*l_0*l_0);
    double mid4=(I_0+m_0*l_0*l_0)/(I_0*(m_0+M_0)+M_0*m_0*l_0*l_0);
    double mid5=m_0*l_0/(I_0*(m_0+M_0)+M_0*m_0*l_0*l_0);
    Amat.resize(4,4);
    Amat.setZero();
    Amat << 0.0, 1.0, 0.0, 0.0,
            0.0,mid1, mid2, 0.0,

            0.0, 0.0, 0.0, 1.0,
            0.0, mid3, mid2, 0.0;
    Bmat.resize(4,1);
    Bmat << 0.0,
            mid4,
            0.0,
            mid5;
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

          double cosTheta = cos(state(2,0));
          double sinTheta = sin(state(2,0));

          double temp = (control_0(0,0) + 5 * pow(state(3,0),2) * sinTheta) / 9;
          double angularAccel = (g_0 * sinTheta - cosTheta * temp) / (
              5 * (4.0 / 3.0 - (2.5 * pow(cosTheta, 2)) / 9));
         double linearAccel = temp - (5 * angularAccel * cosTheta) / 9;

          state(0,0) = state(0,0) + 0.001*delta_t * state(1,0);
          state(1,0) = state(1,0) + 0.001*delta_t * linearAccel;

          state(2,0) = (
              state(2,0) + 0.001*delta_t * state(3,0));
          state(3,0) = (state(3,0)+ 0.001*delta_t * angularAccel);
            if(state(2,0)>2*3.1415926535)
            {
                state(2,0)=state(2,0)-2*3.1415926535;
            }
            if(state(2,0)<-2*3.1415926535)
            {
                state(2,0)=state(2,0)+2*3.1415926535;
            }

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
