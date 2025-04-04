﻿#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "xmlcore.h"
#include <cmath>
#include <MyMath/MyMathLib.h>
#include <swarm_ETMActivator.h>
#include <random>
#include <utility>

// Define pi as a constant
Eigen::MatrixXd originalvector;
double yip=0.8;
int counter=0;
int probability_denominator=22;//总时长60s，平均触发间隔1.2s，(0.12/0.0.3)
inline double ValueOperator(Eigen::MatrixXd value)
{
    return abs(calculateAngleBetweenVectors(originalvector,value));
}
inline double sigma_1_norm(double value)
{
    return 1/sqrt(1+pow(value,2));
}
inline double nuoh(double value)
{
    double h=0.5;
    if(value >=0 && value <=h)
    {
        return 1;
    }
    if(value >=h && value <=1)
    {
        return 0.5*(1+cos(3.1415926535*(value-h)/(1-h)));
    }
    return 0;
}
inline double phibeta(double var)
{
    double dbeta=2;
    return nuoh(var/dbeta)*(sigma_1_norm(var-dbeta)-1);
}
vehicle::vehicle():SwarmAgent()
{
    cacheSigma=1;
    status_num=3;
    action_num=2;
    sigma=cacheSigma;
    cacheOBSclpnum=0;
    TriggerEvent();
}


void vehicle::state_update()
{
    heading_angle=normalize( state_vector(2,0));
    state_vector(2,0)=heading_angle;
    pos_xy(0,0)=state_vector(0,0);
    pos_xy(1,0)=state_vector(1,0);
    vel_xy(0,0)=act_vector(0,0)*cos(heading_angle);
    vel_xy(1,0)=act_vector(0,0)*sin(heading_angle);
    selfETM<<pos_xy(0,0),pos_xy(1,0),vel_xy(0,0),vel_xy(1,0);
}

void vehicle::sensorfunction()
{
    TriggerEvent();
    //这里开始记录数据
    //需要一个更好的格式数据，但是他丫的只有2个维度
    //考虑到触发数据是生造的，这里只记录各自的轨迹数据得了
    logger->log(internalcount,0,pos_xy.coeff(0,0));
    logger->log(internalcount,1,pos_xy.coeff(1,0));
    logger->log(internalcount,2,vel_xy.coeff(0,0));
    logger->log(internalcount,3,vel_xy.coeff(1,0));
    internalcount++;

    //记录触发的时候只需要记录一次就行
    double ei;
    Eigen::MatrixXd temp;
    Eigen::MatrixXd *var=ETM_sensor.value(ID);
    temp=var->block(0,0,4,1)-selfETM;
    ei=temp.norm();
    double pi;
    pi=syncP.norm();

    //还是使用概率触发吧
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, probability_denominator - 1);

    int random_num = dis(gen);

    if (random_num == 0) {
        //简单触发律
        TriggerEvent();
        logger->log(internalcount,4,1);//0代表未被触发，1代表被触发
    }
    else
    {
        logger->log(internalcount,4,0);//0代表未被触发，1代表被触发
    }
    //看来必须使用某种方式进行预测才行
    if(internalcount>1000)//30秒，600个触发时刻
    {
        logger->savexlsfile();
    }
}

void vehicle::timerEvent(QTimerEvent *event)
{
}

void vehicle::broadcastfunction()
{

}

void vehicle::controlfunction()
{
    if(ID==4)//领导者
    {
        //先直线运动规律
        act_vector<<1.5,0.08;
    }
    if(ID<4)//追随者
    {
        Get_sync_error(syncP);
        to_steering(act_vector);
    }
}

bool vehicle::stable_judgement()
{
    return false;
}

void vehicle::predicitTraj()
{
    m_timerid1=startTimer(15000);
}

void vehicle::Getcontrol()
{

}

void vehicle::Getlookaheadpoint()
{

}
void vehicle::setsendsig(int order)
{

}

void vehicle::to_steering(Eigen::MatrixXd &mat)
{
    Eigen::MatrixXd l_i;
    l_i=vel_xy;
    double uxi=vel_xy(0,0);
    double uyi=vel_xy(1,0);
    Eigen::MatrixXd linearspeed;
    Eigen::MatrixXd orien=l_i;
    orien(0,0)=cos(heading_angle);
    orien(1,0)=sin(heading_angle);
    linearspeed=orien.transpose()*(l_i+mat*0.03);//线速度控制量
    linear=linearspeed(0,0);
    double thetaHat=atan2(uyi,uxi);//rad
    //这里的角度有一个吊诡的事情，就是通过0度临界角度的时候，控制量会剧烈抖动
    double dthetaHat=0;
    if(uyi==uxi && uyi==0)
    {
        dthetaHat=0;
    }
    else
    {
        dthetaHat=uxi/(uxi*uxi+uyi*uyi)*mat(1,0)-uyi/(uxi*uxi+uyi*uyi)*mat(0,0);
    }

    if(sigma*thetaHat<0 && ID==3)
    {
        //按时越过临界角度
        qDebug()<<"thetaHat:"<<thetaHat<<" dthetaHat:"<<dthetaHat<<" last_thetaHat:"<<sigma
               <<" manipulating:"<<omega<<" heading_angle:"<<heading_angle;
    }
    sigma=thetaHat;
    double miu_1=1;
    double miu_2=0.5;
    //这里omega稍微优化一下，需要正向转向！
    omega=miu_1*((thetaHat-heading_angle))+miu_2*(dthetaHat-omega);


    //用最大限制一下:
    double maxlinear=30;
    double maxomega=20;
    if(linear<0)
    {
        linear=0;
    }
    if(abs(linear)>maxlinear)
    {
        linear=linear/abs(linear)*maxlinear;
    }//可以在稳定后开启不允许倒车的约束

    if(abs(omega)>maxomega)
    {
        omega=omega/abs(omega)*maxomega;
    }
    act_vector(0,0)=linear;
    act_vector(1,0)=omega;
}

void vehicle::Get_sync_error(Eigen::MatrixXd &mat)
{
    Eigen::MatrixXd n_ij;n_ij.resize(2,1);n_ij.setZero();
    Eigen::MatrixXd grad=n_ij;
    Eigen::MatrixXd grad1=n_ij;
    Eigen::MatrixXd gradient_term=n_ij;
    Eigen::MatrixXd concencus=n_ij;
    Eigen::MatrixXd chasing_term=n_ij;
    Eigen::MatrixXd vec_4d;
    vec_4d.resize(4,1);
    vec_4d.setZero();
    Eigen::MatrixXd *ETMstate;


    Eigen::MatrixXd avergae_vel;
    avergae_vel.resize(2,1);
    avergae_vel.setZero();
    int jnum=1;
    avergae_vel=vel_xy;

    if(ID<agentnum)
    {
        for(int j=1;j<=neib_num+1;j++)
        {
            if(j!=ID)
            {
                ETMstate=ETM_sensor.value(j);
                if(nearbyagentdistance.contains(j))
                {
                    double distance=nearbyagentdistance.value(j);
                    avergae_vel+=ETMstate->block(2,0,2,1);
                    Eigen::MatrixXd n_ij=ETMstate->block(0,0,2,1)-pos_xy;
                    concencus+=ETMstate->block(2,0,2,1)-vel_xy;
                    double norm_2=n_ij.norm();
                    Eigen::MatrixXd grad=(norm_2-distance)*n_ij.normalized();
                    gradient_term+=grad;
                }
            }


        }

        avergae_vel/=jnum;
        act_vector=(concencus+gradient_term);
        //下面添加避障项
        double dot=0;
        double vel_mag;
        Eigen::MatrixXd edge0;
        Eigen::MatrixXd norm;
        Eigen::MatrixXd edge1;
        Eigen::MatrixXd edge2;
        Eigen::MatrixXd beta_agent_control;
        beta_agent_control.resize(2,1);
        norm.resize(2,1);
        beta_agent_control.setZero();
        gradient_term.setZero();
        edge0=beta_agent_control;
        edge1=edge0=edge2=edge0;
        concencus.setZero();
        Eigen::MatrixXd pos_close_agent=edge0;

        for(int j=1;j<=obs_closet_point_num;j++)
        {
            ClosePoint *close_agent=closepoint_map.value(j);


            edge1(0,0)=close_agent->edge1_x;
            edge1(1,0)=close_agent->edge1_y;

            edge2(0,0)=close_agent->edge2_x;
            edge2(1,0)=close_agent->edge2_y;

            pos_close_agent(0,0)=close_agent->x;
            pos_close_agent(1,0)=close_agent->y;
            Eigen::MatrixXd posofcp;
            posofcp=pos_close_agent;

            originalvector=avergae_vel;
            if (close_agent->edg2==-close_agent->edg1)
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

            vel_mag=vel_xy.norm();
            edge0.normalize();//vel of beta ganet
            beta_agent_control=vel_mag*edge0;//vel of beta ganet
            close_agent->angle=get_angle(beta_agent_control(0,0),beta_agent_control(1,0));
            norm=beta_agent_control-vel_xy;
            concencus=concencus+norm;
            norm=pos_close_agent-pos_xy;
            dot=norm.norm();
            grad=(dot-communication_range)/pow(dot,2)*norm;

            Eigen::MatrixXd n_i_j_hat=(posofcp-pos_xy)/sqrt(1+yip*pow((posofcp-pos_xy).norm(),2));
            gradient_term=gradient_term+10/(posofcp-pos_xy).norm()*(-n_i_j_hat);
        }
        act_vector=act_vector+(concencus+10*gradient_term);
        return;
    }

}
void vehicle::fault_set(int option)
{
    xmlreader= new xmlCore(config_file.toStdString());
    xmlreader->xmlRead("agent_num",agentnum);

    Eigen::MatrixXd relationmatrix;
    relationmatrix.resize(agentnum,agentnum);
    xmlreader->xmlRead("relationmatrix",relationmatrix);

    for(int k=0;k<agentnum;k++)
    {
        if(relationmatrix(ID-1,k)!=0)
        {
            nearbyagentdistance.insert(k+1,relationmatrix(ID-1,k));
        }
    }

    //初始化容器
    logger=swarm_ETMActivator::getService<Datalogservice>("Datalogservice");
    this->logger=logger->cloneservice();
    QString filename="./log/ETM_Agent_"+QString::number(ID)+".xls";
    this->logger->createlogfile("./log/ETM_Agent_"+QString::number(ID)+".txt",6066+ID);
    this->logger->DeleteFile(filename);
    this->logger->createxlsfile(filename);


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

void vehicle::Broadcastupdate(Eigen::MatrixXd e_t, Eigen::MatrixXd v_t, Eigen::MatrixXd v_n, Eigen::MatrixXd othersignal)
{

}
