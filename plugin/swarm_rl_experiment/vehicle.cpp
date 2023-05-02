#include "vehicle.h"

vehicle::vehicle():SwarmAgent()
{
    status_num=3;
    action_num=2;
    communication_range=5;
    collision_r=2.5;
    heading_angle=0;
    falseflag=0;
}


void vehicle::state_update()
{
    heading_angle=state_vector(2,0);
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
    act_vector<<4,1;
}

void vehicle::fault_set(int option)
{
    falseflag=option;

}

SwarmAgent *vehicle::clone_agent()
{
    vehicle *new_vehicle=new vehicle;
    return new_vehicle;
}

Eigen::MatrixXd vehicle::state_space_equation()
{
    Eigen::MatrixXd d_state;
    d_state.resize(3,1);
    d_state.setZero();
    if(falseflag==0)
    {
        double angle=state_vector(2,0);
        d_state(0,0)=act_vector(0,0)*cos(angle);
        d_state(1,0)=act_vector(0,0)*sin(angle);
        d_state(2,0)=act_vector(1,0);

    }
    else
    {

    }
    return d_state;
}
