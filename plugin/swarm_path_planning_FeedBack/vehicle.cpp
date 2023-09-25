#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "xmlcore.h"
#include <cmath>
#include <MyMath/MyMathLib.h>
#include <swarm_path_planning_FeedBackActivator.h>


vehicle::vehicle():SwarmAgent()
{

    status_num=3;
    action_num=2;
    TriggerTimecounter=0;
    sigma_step=-1;
    timenow=0;
    maxmumstep=10;
    Trackref.resize(maxmumstep,5);
    Trackref.setZero();
    TriggerEvent();
    //动力学不变

    InternalState.resize(3,1);
    InternalState<<1,1,1;//初始化位置，可以按照文件来初始化


  //  predictedN

    selfETM.resize(3,1);
    selfETM.setZero();

    QString filename="./config/swarmmpc/swarm.xml";
    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("decnum",predictedN);
}


void vehicle::state_update()
{

    heading_angle=normalize( state_vector(2,0));
    state_vector(2,0)=heading_angle;
    pos_xy(0,0)=state_vector(0,0);
    pos_xy(1,0)=state_vector(1,0);
    vel_xy(0,0)=act_vector(0,0)*cos(heading_angle);
    vel_xy(1,0)=act_vector(0,0)*sin(heading_angle);
    selfETM<<pos_xy(0,0),pos_xy(1,0),heading_angle;


}

void vehicle::sensorfunction()
{

    if(ID<agentnum)
    {
        if(TriggerTimecounter>sigma_step)
        {
            TriggerEvent();
            TriggerTimecounter=0;
        }
        TriggerTimecounter++;
    }
    else
    {
        TriggerEvent();//这个没有意义，只是为了下面的循环方便一点
    }

}

void vehicle::broadcastfunction()
{


}

void vehicle::controlfunction()
{
    //确认是否收到了所有的agent的信息
    if(ID<agentnum)
    {
        trackref();
        return;
    }
    if(ID==agentnum)
    {
        int counter=0;
        for(int i=1;i<=agentnum;i++)
        {
            if(ETM_Flag[i]==1 && i!=ID)
            {
                counter++;
            }
        }
        if(counter==agentnum-1)
        {
            //执行重规划
            Eigen::MatrixXd states_of_all;
            states_of_all.resize(agentnum,3);
            states_of_all.setZero();
            for(int i=1;i<=agentnum;i++)
            {
                states_of_all(i-1,0)=ETM_sensor.value(i)->coeffRef(0,0);//x
                states_of_all(i-1,1)=ETM_sensor.value(i)->coeffRef(1,0);//y
                states_of_all(i-1,2)=ETM_sensor.value(i)->coeffRef(2,0);//phi
            }
            Eigen::MatrixXd TargetTraj;
            predicitTraj(TargetTraj);

            Eigen::MatrixXd Planedtraj;
            m_planner->plan(states_of_all,TargetTraj,Planedtraj);
//            emit LeaderBroadcast(Planedtraj);
//            Trackref=Planedtraj.block(0,5*(ID-1),Planedtraj.rows(),5);

            trackref();
            //好的，外部工程似乎都完成了
        }
        else
        {
            //执行轨迹追踪
            trackref();
        }

        return;
    }

}

bool vehicle::stable_judgement()
{
    return false;
}

void vehicle::predicitTraj(Eigen::MatrixXd &target)
{
    //此处维持一个内在变量
    Eigen::MatrixXd d_state;
    double v=1;
    double omega=0.15;//设计一个圆弧轨迹，当然也可以用internalcounter计算
    d_state.resize(3,1);
    d_state.setZero();
    //这样设计的好处是，可以自动生成轨迹点，而无需外部再写一个轨迹生成器
    double angle=InternalState(2,0);
    d_state(0,0)=v*cos(angle);
    d_state(1,0)=v*sin(angle);
    d_state(2,0)=omega;
    target.resize(predictedN,3);
    target.setZero();
    for(int i=0;i<predictedN;i++)
    {
        angle=InternalState(2,0);
//        angle=normalize(angle);
        d_state(0,0)=v*cos(angle);
        d_state(1,0)=v*sin(angle);
        d_state(2,0)=omega;
        InternalState=InternalState+0.03*d_state;

        target.block(i,0,1,3)=InternalState.transpose();
        internalcount++;
    }
    emit Predictbroadcast(target);
}

void vehicle::Getcontrol()
{
    //这一步在Getlookaheadpoint完成了

}

void vehicle::Getlookaheadpoint()
{

}
void vehicle::setsendsig(int order)
{


    qRegisterMetaType<Eigen::MatrixXd>("Eigen::MatrixXd");
    if(order==0)//也就是本机为leader
    {
        swarm_path_planning_FeedBackActivator::publishsignal(this,SIGNAL(LeaderBroadcast(Eigen::MatrixXd))
                                                             ,"LeaderBroadCast",Qt::DirectConnection);
        swarm_path_planning_FeedBackActivator::publishsignal(this,SIGNAL(Predictbroadcast(Eigen::MatrixXd))
                                                             ,"Predictbroadcast",Qt::QueuedConnection);

    }
    if(order==1)//也就是本机为follower
    {

        swarm_path_planning_FeedBackActivator::subscribeslot(this,SLOT(Recievesig(Eigen::MatrixXd))
                                                             ,"LeaderBroadCast",
                                                             Qt::DirectConnection);
    }
}

void vehicle::trackref()
{
    act_vector(0,0)=Trackref(timenow,3);
    act_vector(1,0)=Trackref(timenow,4);
    //这里追踪比较呆，不考虑动态
    timenow++;
    if(timenow>=maxmumstep)
    {
        timenow=maxmumstep-1;//取最后一个以防万一
    }
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

    Eigen::MatrixXd d_state;
    d_state.resize(3,1);
    d_state.setZero();

    double angle=state_vector(2,0);
    d_state(0,0)=act_vector(0,0)*cos(angle);
    d_state(1,0)=act_vector(0,0)*sin(angle);
    d_state(2,0)=act_vector(1,0);


    return d_state;

}

void vehicle::Recievesig(Eigen::MatrixXd PlannedTraj)
{
    //将自己部分的轨迹解包
    int col=PlannedTraj.cols();
    int row=PlannedTraj.rows();
    Trackref.resize(row,5);//xyyphivw,时刻
    //这里记着phi需要正规化！！
    Trackref.setZero();
    for(int i=0;i<row;i++)
    {
        PlannedTraj(i,5*(ID-1)+2)=normalize(PlannedTraj(i,5*(ID-1)+2));
    }
    Trackref=PlannedTraj.block(0,5*(ID-1),row,5);
    //此外，还有都需要的，额外的信息：到下一时刻前的最大步数
    maxmumstep=PlannedTraj(0,5*agentnum);
    //注意，最大时刻是按照时间触发机制计算的
    //不是按照行数算的
    timenow=0;
}
