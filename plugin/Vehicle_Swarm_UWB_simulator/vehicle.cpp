#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "xmlcore.h"
#include <cmath>
#include <MyMath/MyMathLib.h>
#include <Vehicle_Swarm_UWB_simulatorActivator.h>
Eigen::MatrixXd originalvector;
int counter=0;

inline double ValueOperator(Eigen::MatrixXd value)
{
    return abs(calculateAngleBetweenVectors(originalvector,value));
}
vehicle::vehicle():SwarmAgent()
{
    cacheOBSclpnum=0;
    internalcount=0;
    cacheSigma=1;
    status_num=3;
    action_num=2;
    act_vector.resize(2,1);
    state_vector.resize(3,1);
    QString filename="./config/DistributedMPC/swarmUWB.xml";

    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    TriggerEvent();
    //动力学不变

    selfETM.resize(5,1);
    selfETM.setZero();
    xmlreader.xmlRead("collision_r",collision_r);
}


void vehicle::state_update()
{

    heading_angle=normalize( state_vector(2,0));
    state_vector(2,0)=heading_angle;
    pos_xy(0,0)=state_vector(0,0);
    pos_xy(1,0)=state_vector(1,0);
    vel_xy(0,0)=act_vector(0,0)*cos(heading_angle);
    vel_xy(1,0)=act_vector(0,0)*sin(heading_angle);
    selfETM<<pos_xy(0,0),pos_xy(1,0),heading_angle,act_vector(0,0),act_vector(1,0);


}

void vehicle::sensorfunction()
{

}
void vehicle::broadcastfunction()
{


}

void vehicle::controlfunction()
{

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
    vehicle *new_vehicle=new vehicle;
    return new_vehicle;
}

Eigen::MatrixXd vehicle::state_space_equation()
{
    Eigen::MatrixXd dstate;
    return dstate;
}

void vehicle::getsolution(Eigen::MatrixXd solution)
{

}
