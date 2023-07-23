#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "xmlcore.h"
#include "Swarm_obstacle_avoidActivator.h"
#include <cmath>

// Define pi as a constant
const double pi = 3.141592653589793;
vehicle::vehicle():SwarmAgent()
{
    QString configfilename="./config/swarm/predict.xml";
    xmlCore Xmlreader(configfilename.toStdString());
    status_num=3;
    action_num=2;
    Xmlreader.xmlRead("communication_range",communication_range);
    Xmlreader.xmlRead("collision_r",collision_r);
    Xmlreader.xmlRead("maxspeed",maxspeed);
    Xmlreader.xmlRead("maxOmega",maxOmega);
    heading_angle=0;
    falseflag=0;

    Xmlreader.xmlRead("predicthorizon",predicthorizon);
    singleone=new HMagent;
    xmlCore xmlreader(configfilename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    SwarmSimservice *swarmsim0=Swarm_obstacle_avoidActivator::getService<SwarmSimservice>("SwarmSimservice");
    SwarmSimservice *swarmsim=swarmsim0->cloneservice();
    swarmsim->init_plant(30,configfilename,singleone);
    agentgroup=swarmsim->getagentgroup();

    dysim=swarmsim->get_simer();
    dysim->set_step_in_mode(1);
    swarmsim->startsim();
}


void vehicle::state_update()
{
    //这里还需要将state_vector的角度化简到合适范围-pi到pi之间
    //这就是应对目标点在身后的方法？

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

double vehicle::normalize(double angle)
{
    // Use fmod to compute the modulo of angle and 2pi
    double remainder = fmod(angle, 2 * pi);
    if(isnan(remainder))
    {
        int a=1;
    }
    // If the remainder is positive and greater than pi, subtract 2pi
    if (remainder > 0 && remainder > pi) {
        remainder -= 2 * pi;
    }
    // If the remainder is negative and less than -pi, add 2pi
    if (remainder < 0 && remainder < -pi) {
        remainder += 2 * pi;
    }
    // Return the normalized angle
    return remainder;
}

void vehicle::broadcastfunction()
{
}

void vehicle::controlfunction()
{
    if(stable_judgement()==false)
    {
        predicitTraj();
        Getlookaheadpoint();
        Getcontrol();
    }
    else
    {
        act_vector(1,0)=0;
        act_vector(0,0)=0;
    }

}

bool vehicle::stable_judgement()
{
    return false;
}

void vehicle::predicitTraj()
{
    //对于非邻居，不能够将其状态设置为一致的，否则就会出现nan
    for(int i=1;i<=agentnum;i++)
    {//先设置所有的邻居状态在范围i外，然后再设置单个邻居状态在范围内
        //超出范围邻居会被灭掉！
        SwarmAgent *sinagent=agentgroup[i];
        sinagent->state_vector.setOnes();//这边超界了？
        sinagent->state_vector= sinagent->ID*10000*sinagent->state_vector;
        sinagent->state_vector(2,0)=0;
        sinagent->state_vector(3,0)=0;

        //不能够简单的通过这种方式移除掉多余的agent!
    }//在这一步设置所有的agent的状态相邻状态设置为相邻状态，其余设置为
    //遥远状态

    //将实际邻居状态赋予邻居
    for(int i=1;i<=neib_num;i++)
    {
        SwarmAgent *nbagent=neib_map[i];
        SwarmAgent *sinagent=agentgroup[nbagent->ID];
        //这一步不小心把邻居状态的变量维度改变了
        sinagent->state_vector(0,0)=nbagent->state_vector(0,0);
        sinagent->state_vector(1,0)=nbagent->state_vector(1,0);
        //上面是x和y
        sinagent->state_vector(2,0)=nbagent->vel_xy(0,0);
        sinagent->state_vector(3,0)=nbagent->vel_xy(1,0);
        //上面是vx和vy
    }
    //设置和自己相等的agent
    SwarmAgent *selagent=agentgroup[this->ID];
    selagent->state_vector(0,0)=state_vector(0,0);
    selagent->state_vector(1,0)=state_vector(1,0);
    selagent->state_vector(2,0)=vel_xy(0,0);
    selagent->state_vector(3,0)=vel_xy(1,0);


    //状态设置完成，进行N步的状态预测以生成轨迹
    //
    for(int j=0;j<predicthorizon;j++)
    {
        dysim->step_in();

    }
    //    my_logger->flush();

}

void vehicle::Getcontrol()
{
    //这一步在Getlookaheadpoint完成了

}

void vehicle::Getlookaheadpoint()
{
    SwarmAgent *sinagent=agentgroup[this->ID];
    double L=(sinagent->pos_xy-pos_xy).norm();
    double deltatheta=normalize(sinagent->heading_angle-this->heading_angle);
    double veltracking=sinagent->vel_xy.norm();
    if(abs(veltracking)>maxspeed)
    {
        if(act_vector(0,0)>0)
        {
            act_vector(0,0)=maxspeed;
        }
        else
        {
            act_vector(0,0)=-maxspeed;
        }
    }
    else
    {
        act_vector(0,0)=veltracking;
    }
    act_vector(1,0)=2*veltracking*sin(deltatheta/2)/L;
    if(abs(act_vector(1,0))>maxOmega)
    {
        if(act_vector(1,0)>0)
        {
            act_vector(1,0)=maxOmega;
        }
        else
        {
            act_vector(1,0)=-maxOmega;
        }
    }
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
