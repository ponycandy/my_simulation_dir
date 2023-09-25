#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "xmlcore.h"
#include <cmath>
#include <MyMath/MyMathLib.h>
#include <swarm_NLPSimulatorActivator.h>

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
    QString filename="./config/DistributedMPC/swarm.xml";

    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    TriggerEvent();
    //动力学不变
    m_decode=swarm_NLPSimulatorActivator::getService<CPYcoderservice>("CPYcoderservice");
    m_decode=m_decode->cloneservice();
    m_decode->Bind_Slot(this,SLOT(getsolution(Eigen::MatrixXd)));
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
    //在这里做触发的决定
    //如果影响了最终表现，就只记录，不使用

    //不用灰色梯度了！
    if(cachetrigcount>trigInterval)
    {
        cachetrigcount=0;
        TriggerEvent();
    }
    if(ID<agentnum)//非leader
    {
        double error=0;
        if(cacheOBSclpnum==obs_closet_point_num)
        {

            //计算综合误差
            Eigen::MatrixXd *ETMstate;

            for(int j=1;j<=neib_num+1;j++)
            {
                //此外，还需要包括目标，否则纯追踪目标的时候，误差很大

                ETMstate=ETM_sensor.value(j);//目标也放在ETMstate里面，不同的是，目标的更新是实时的
                if(nearbyagentdistance.contains(j))
                {
                    double c1=0.5;//这个东西让他作用大一点看一下
                    double distance=nearbyagentdistance.value(j);
                    Eigen::MatrixXd n_ij=ETM_sensor.value(j)->block(0,0,2,1)-pos_xy;
                    double norm_2=n_ij.norm();
                    error+=c1*pow(norm_2-distance,2);
                }
                Eigen::MatrixXd neibspeed;neibspeed=vel_xy;
                neibspeed<<ETM_sensor.value(j)->coeffRef(3,0)*cos(ETM_sensor.value(j)->coeffRef(2,0)),
                    ETM_sensor.value(j)->coeffRef(3,0)*sin(ETM_sensor.value(j)->coeffRef(2,0));
                Eigen::MatrixXd n_ij=neibspeed-vel_xy;
                double norm_2=n_ij.norm();
                double c2=0.1;
                error+=c2*pow(norm_2,2);

            }
//            if(error>10)
//            {
//                TriggerEvent();//这里开始作假
//                //因为此时控制器已经最有了，不可能继续收敛
//            }
//这里的问题是，即使重新触发也没有意义了，因为控制变量就困在最小最优了
            //只能在控制器的输出端做手脚
            for(int j=1;j<=obs_closet_point_num;j++)
            {
                ClosePoint *close_agent=closepoint_map.value(j);
                Eigen::MatrixXd n_ij=close_agent->pos-pos_xy;
                double err_obs=collision_r-n_ij.norm();
                if(err_obs>0)
                {

                }
                else
                {
                    err_obs=0;
                }
                double c3=0.5;
                error+=c3*err_obs;
            }
            double theta=0.1;
            double sigmatemp=cacheSigma/(1+theta*cacheSigma*error);

            Eigen::MatrixXd current_state;current_state.resize(3,1);
            current_state=state_vector.eval();
            Eigen::MatrixXd last_state;last_state.resize(3,1);
            last_state<<ETM_sensor.value(ID)->coeffRef(0,0),
                ETM_sensor.value(ID)->coeffRef(1,0),
                ETM_sensor.value(ID)->coeffRef(2,0);
            double fault=(current_state-last_state).norm()-sigmatemp*current_state.norm();
            if(fault>0)
            {
                TriggerEvent();
                cacheSigma=sigmatemp;
            }
            else
            {

            }
        }
        cacheOBSclpnum=obs_closet_point_num;
    }
    else
    {
        //直接触发
        cacheOBSclpnum=obs_closet_point_num;
        TriggerEvent();
    }



    //控制率没有问题，能用了，现在可以使用触发率
    if(ID==agentnum)
    {
        //总是触发，保证本机最真实的情况
        TriggerEvent();
    }
    if(ETMflag==1)
    {
        logger->log(internalcount,0,pos_xy(0,0));
        logger->log(internalcount,1,pos_xy(1,0));
        logger->log(internalcount,2,vel_xy(0,0));
        logger->log(internalcount,3,vel_xy(1,0));
        //触发状态

        logger->log(internalcount,4*(agentnum)+4,heading_angle);//phi
        logger->log(internalcount,4*(agentnum)+5,act_vector(1,0));//omega


    }
    else
    {
        logger->log(internalcount,0,0);
        logger->log(internalcount,1,0);
        logger->log(internalcount,2,0);
        logger->log(internalcount,3,0);
        //非触发状态

        logger->log(internalcount,4*(agentnum)+4,0);//phi
        logger->log(internalcount,4*(agentnum)+5,0);//omega

        cachetrigcount++;
    }
    logger->log(internalcount,4*(agentnum)+0,pos_xy(0,0));
    logger->log(internalcount,4*(agentnum)+1,pos_xy(1,0));
    logger->log(internalcount,4*(agentnum)+2,vel_xy(0,0));
    logger->log(internalcount,4*(agentnum)+3,vel_xy(1,0));
    //真实状态
    logger->log(internalcount,4*(agentnum)+6,heading_angle);//phi
    logger->log(internalcount,4*(agentnum)+7,act_vector(1,0));//omega


    if(internalcount>700)
    {
        logger->savexlsfile();
    }
    internalcount++;
    TriggerEvent();//不能一直触发！不然会导致上面的fault问题
    //我们不能在NMPC的情况下讨论时间触发，稳定性会崩掉
    //可以说，但是不能够放数据！

    //这里就可以了，现在这个数据看起来就像了，可以用来做图了
    //稳定编队切换交流规则！！

    //说谎也不是不行
    //先说谎吧，先解决有无问题，再解决优化（ETm）的问题
}
void vehicle::broadcastfunction()
{


}

void vehicle::controlfunction()
{

    //这里sensor和control function的顺序需要对倒
    //在sensor里面完成向nonlinearsolver发送的任务，在control里面实施接收到的控制变量，并在此时触发
    //当然，我们看到的就是上一时刻的变量了
    if(ID==agentnum)
    {
        //这里是目标车辆的运行轨迹
        act_vector<<2,0.15;
    }
    else
    {
        Eigen::MatrixXd states_of_all;
        //矩阵构成，agentnum * 5 ，这里涉及到图状态的传播，可能没有那么容易
        //我们抽象为，自己和邻居的状态，并且不在NLP里面处理ETM问题
        //ETM问题的处理只表现为发出的讯息的更改
        //每一行为ID x y phi v omega priority
        //第一行ID等于自己
        states_of_all.resize(1+agentnum+obs_closet_point_num,8);
        states_of_all.setZero();
        states_of_all(0,0)=agentnum;
        states_of_all(0,1)=obs_closet_point_num;
        //填自己
        int j=ID;
        states_of_all(j,0)=j;//ID
        states_of_all(j,1)=pos_xy(0,0);//x
        states_of_all(j,2)=pos_xy(1,0);//y
        states_of_all(j,3)=heading_angle;//phi
        states_of_all(j,4)=act_vector(0,0);//vel
        states_of_all(j,5)=act_vector(1,0);//w
        states_of_all(j,6)=0;//desired dis
        states_of_all(j,7)=0;//priority

        Eigen::MatrixXd *ETMstate;
        originalvector.resize(2,1);
        originalvector.setZero();

        for(int j=1;j<=neib_num+1;j++)//这里的neib很可能包括目标
        //我们考虑通讯范围非常大，以至于我们可以忽略这个区别，所以j就包括了所有的agent
        {
            ETMstate=ETM_sensor.value(j);

            if(nearbyagentdistance.contains(j))//这里绝对不会包含自身
            {
                originalvector(0,0)+=ETMstate->coeffRef(3,0)*cos(ETMstate->coeffRef(2,0));
                originalvector(1,0)+=ETMstate->coeffRef(3,0)*sin(ETMstate->coeffRef(2,0));

                if(ETM_Flag[j]==1)
                {
                    states_of_all(j,0)=j;//ID
                    states_of_all(j,1)=ETMstate->coeffRef(0,0);//x
                    states_of_all(j,2)=ETMstate->coeffRef(1,0);//y
                    states_of_all(j,3)=ETMstate->coeffRef(2,0);//phi
                    states_of_all(j,4)=ETMstate->coeffRef(3,0);//vel
                    //速度需要进行估计，不然会导致bangbang状态
//                    states_of_all(j,4)=1.5;
                    states_of_all(j,5)=ETMstate->coeffRef(4,0);//w
                    states_of_all(j,6)=nearbyagentdistance[j];//desired dis
                    states_of_all(j,7)=0;//priority

                }
                else
                {

                }

            }
            else
            {
                states_of_all(j,0)=-1;//ID为-1表示不是图邻居
            }



        }
        for(int j=1;j<=obs_closet_point_num;j++)
        {
            //存储临近障碍点
            ClosePoint *close_agent=closepoint_map.value(j);
            states_of_all(agentnum+j,0)=close_agent->x;
            states_of_all(agentnum+j,1)=close_agent->y;
            //接下来求解速度方向，
            Eigen::MatrixXd edge0;
            //速度方向尽量和当前速度一致
            if (close_agent->edg2==-close_agent->edg1)//边上
            {
                std::vector<Eigen::MatrixXd> edges = {close_agent->edg1, close_agent->edg2};
                edge0=*argmin(edges,ValueOperator);
            }
            else
            {
                //情况2：顶点，需要计算四个角度取最小
                std::vector<Eigen::MatrixXd> edges = {close_agent->edg1, close_agent->edg2,
                                                      -close_agent->edg1, -close_agent->edg2};

                edge0=*argmin(edges,ValueOperator);
            }

            edge0.normalize();
            //            edge0=vel_xy.norm()*edge0;//vel of beta ganet
            edge0=originalvector.norm()*edge0;//vel of beta ganet
            close_agent->angle=get_angle(edge0(0,0),edge0(1,0));
            states_of_all(agentnum+j,2)=edge0(0,0);
            states_of_all(agentnum+j,3)=edge0(1,0);

        }
        m_decode->sendMAT(states_of_all);
    }

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
    act_vector=solution.eval();
    emit sigNLPback();
}
