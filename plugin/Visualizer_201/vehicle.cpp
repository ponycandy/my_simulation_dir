#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "xmlcore.h"
#include <cmath>
#include <MyMath/MyMathLib.h>
#include <Visualizer_201Activator.h>

vehicle::vehicle(QString filename):SwarmAgent()
{
    m_filename=filename;
    cacheOBSclpnum=0;
    internalcount=0;
    cacheSigma=1;
    status_num=3;
    action_num=2;
    act_vector.resize(2,1);
    state_vector.resize(3,1);

    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    TriggerEvent();

    selfETM.resize(5,1);
    selfETM.setZero();

    xmlreader.xmlRead("collision_r",collision_r);//邻居的检测半径
}


void vehicle::state_update()
{

    heading_angle=normalize( state_vector(2,0));
    state_vector(2,0)=heading_angle;
    pos_xy(0,0)=state_vector(0,0);
    pos_xy(1,0)=state_vector(1,0);
    vel_xy(0,0)=act_vector(0,0)*cos(heading_angle);
    vel_xy(1,0)=act_vector(0,0)*sin(heading_angle);
}

void vehicle::sensorfunction()
{

}
void vehicle::broadcastfunction()
{


}

void vehicle::controlfunction()
{
    act_vector<<10,0;
}







void vehicle::setsendsig(int order)
{



}

void vehicle::implementcontrol()
{

}

void vehicle::fault_set(int option)
{


}


SwarmAgent *vehicle::clone_agent()
{
    vehicle *new_vehicle=new vehicle(m_filename);
    return new_vehicle;
}

Eigen::MatrixXd vehicle::state_space_equation()
{

    Eigen::MatrixXd d_state;
    d_state.resize(3,1);
    d_state.setZero();
    double angle=state_vector(2,0);
    d_state(0,0)=act_vector(0,0)*cos(angle);
    d_state(1,0)=act_vector(0,0)*sin(angle);
    d_state(2,0)=act_vector(1,0);
    return d_state;
}

void vehicle::getsolution(Eigen::MatrixXd solution)
{
}
