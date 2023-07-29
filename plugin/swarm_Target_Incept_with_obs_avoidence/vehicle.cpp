#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "xmlcore.h"
#include "swarm_Target_Incept_with_obs_avoidenceActivator.h"
#include <cmath>

// Define pi as a constant
const double pi = 3.141592653589793;
vehicle::vehicle():SwarmAgent()
{
    m_e_T.resize(2,1);
    m_e_T.setZero();
    m_v_T.resize(2,1);
    m_v_T.setZero();
    m_v_n=m_v_T;
    QString configfilename="./config/swarmInception/swarm.xml";
    xmlCore Xmlreader(configfilename.toStdString());
    Xmlreader.xmlRead("agent_num",agentnum);
    status_num=4;
    action_num=2;
    Xmlreader.xmlRead("communication_range",communication_range);
    Xmlreader.xmlRead("collision_r",collision_r);
    Xmlreader.xmlRead("sensor_range",sensor_range);
    heading_angle=0;
    falseflag=0;

    Xmlreader.xmlRead("predicthorizon",predicthorizon);

    steps=0;//用来记录
}
double vehicle::get_angle(double vx, double vy)
{
    double value=0;
    if(isnan(vy/vx))
    {
        return value;

    }
    else
    {
        value=atan2(vy,vx);
        if(isnan(value))
        {
            return 0;
        }
        return  value;
    }
}

void vehicle::state_update()
{

    if(ID<agentnum)
    {
        pos_xy(0,0)=state_vector(0,0);
        pos_xy(1,0)=state_vector(1,0);
        vel_xy(0,0)=state_vector(2,0);
        vel_xy(1,0)=state_vector(3,0);
        heading_angle=get_angle(vel_xy(0,0),vel_xy(1,0));
    }
    else
    {
        heading_angle=normalize( state_vector(2,0));
        state_vector(2,0)=heading_angle;
        pos_xy(0,0)=state_vector(0,0);
        pos_xy(1,0)=state_vector(1,0);
        vel_xy(0,0)=act_vector(0,0)*cos(heading_angle);
        vel_xy(1,0)=act_vector(0,0)*sin(heading_angle);
    }
}

void vehicle::sensorfunction()
{
    Eigen::Matrix<double,2,1> constantmat;
    constantmat<<0,0;//constant可以随着队形方向发生改变，好像书上是有
    //这部分的，咱们最好加进来，因为旋转自由度我们似乎从未控制过
    if(ID==agentnum-1)//for leader
    {
        //leader无法使用一般的neib_aget判断方式
        //它的neib_agent是单方面的,我们应该在
        //主程序中使用或者判断
        //然后再在各个agent里面做详细判断（是否为agent）
        //框架只反映是否受影响
        for(int j=1;j<=sensor_subject_num;j++)
        {
            SwarmAgent *subject=sensor_subject_map.value(j);
            if(subject->ID == agentnum)//探测到目标
            {
                m_e_T=subject->pos_xy-pos_xy-constantmat;
                m_v_T=subject->vel_xy-vel_xy;
            }
        }
        m_v_n=vel_xy;
    }
}

double vehicle::normalize(double angle)
{
    double remainder = fmod(angle, 2 * pi);
    if(isnan(remainder))
    {
        int a=1;
    }
    if (remainder > 0 && remainder > pi) {
        remainder -= 2 * pi;
    }
    if (remainder < 0 && remainder < -pi) {
        remainder += 2 * pi;
    }
    return remainder;
}

void vehicle::broadcastfunction()
{

    if(ID==agentnum)//如果是Targetagent
    {
        updatetarget(pos_xy(0,0),pos_xy(1,0),heading_angle);
        return;
    }

    if(ID==agentnum-1)//如果是Leader
    {
        updateleader(pos_xy(0,0),pos_xy(1,0),heading_angle);
        LeaderBroadcast(m_e_T,m_v_T,m_v_n);
        //上面的值在感知函数中计算
        return;
    }

}


void vehicle::controlfunction()
{
    if(ID==agentnum)//给目标设置一个合适的运动轨迹,目前绕圈比较好，我们设置vel但是不设置act
    {
        act_vector<<1,0.05;
        //        act_vector.setZero();
        return;
    }
    if(ID==agentnum)
    {
        //这里给一个flag，我们在此做一个整体变形的最优化
    }
    if(ID<=agentnum-1)//领导者可以考虑加入一些人类的先验知识
    {
        double const ka=0.8;
        Eigen::MatrixXd concencus;
        concencus.resize(2,1);
        concencus.setZero();
        Eigen::MatrixXd gradient_term=concencus;
        for(int j=1;j<=neib_num;j++)
        {
            SwarmAgent *neib_agent=neib_map.value(j);

            if(nearbyagentdistance.contains(neib_agent->ID))//错了！！
            {
                double distance=nearbyagentdistance.value(neib_agent->ID);
                Eigen::MatrixXd n_ij=neib_agent->pos_xy-pos_xy;
                concencus+=neib_agent->vel_xy-vel_xy;
                double norm_2=n_ij.norm();


                Eigen::MatrixXd grad=(norm_2-distance)/pow(norm_2,2)*n_ij;
                //这里的插值必须选择为一个给定的小于通讯半径的值，我们总是选择0.5*communication_range
                //当然，这个距离可以被设计用来编队
                gradient_term+=grad;
            }

        }
        //这里不再有chasing term
        act_vector=(concencus+4*gradient_term);//目前，只有共识和互斥项
        //下面添加避障项:
        gradient_term.setZero();
        concencus.setZero();
        Eigen::MatrixXd edge0;
        Eigen::MatrixXd beta_agent_control;
        Eigen::MatrixXd posofcp;
        Eigen::MatrixXd grad;
        posofcp.resize(2,1);
        grad=posofcp;
        for(int j=1;j<=obs_closet_point_num;j++)
        {
            ClosePoint *close_agent=closepoint_map.value(j);
            double dot = (vel_xy.transpose() * close_agent->edg1)(0,0);
            if(dot>=0)
            {
                edge0=close_agent->edg1;
            }
            else
            {
                edge0=close_agent->edg2;
            }
            double vel_mag=vel_xy.norm();
            edge0.normalize();//vel of beta ganet
            beta_agent_control=-vel_mag*edge0;//vel of beta ganet
            close_agent->angle=get_angle(beta_agent_control(0,0),beta_agent_control(1,0));
            concencus+= concencus+beta_agent_control-vel_xy;
            posofcp<<close_agent->x,close_agent->y;
            dot=(posofcp-pos_xy).norm();

            grad=(dot-communication_range)/pow(dot,2)*(posofcp-pos_xy);
            gradient_term=gradient_term+grad;

        }
        act_vector=act_vector+(concencus+5*gradient_term);
        //到此加上了避障项
        //下面添加目标项
        gradient_term.setZero();
        concencus.setZero();
        double const Kt=5;
        Eigen::MatrixXd h;
        h=Kt*m_e_T+m_v_T; //第二项的控制与第一项冲突？

        //        M_logger->log(QString(" m_v_T is ")+QString::number(m_v_T(0,0))+" "+QString::number(m_v_T(1,0)),2);
        //        M_logger->log(QString(" h is ")+QString::number(h(0,0))+" "+QString::number(h(1,0)),2);

        //        act_vector+=h;
        //这一项可以保证leader移动到目标附件，但是保证不了全局收敛

        //添加速度误差项
        if(ID==agentnum-1)
        {
            act_vector+=h;
            //            M_logger->log(QString(" ex is ")+QString::number(m_e_T(0,0))+" ev is "+QString::number(m_v_T(0,0))+" control is "+QString::number(act_vector(0,0)),2);

            //有静态误差，说明targetagent对目标施加了力
            //这个静态误差是哪里来的？

        }
    }
}
bool vehicle::stable_judgement()
{
    return false;
}

void vehicle::predicitTraj()
{


}

void vehicle::Getcontrol()
{

}

void vehicle::Getlookaheadpoint()
{

}

void vehicle::fault_set(int option)
{
    falseflag=option;

}

void vehicle::setsendsig(int order)
{
    qRegisterMetaType<Eigen::MatrixXd>("Eigen::MatrixXd");
    if(order==0)//也就是本机为target
    {
        swarm_Target_Incept_with_obs_avoidenceActivator::publishsignal(this,SIGNAL(updatetarget(double,double,double))
                                                                       ,"Targetstateupdatesig",Qt::QueuedConnection);
    }
    if(order==1)//也就是本机为leader
    {
        swarm_Target_Incept_with_obs_avoidenceActivator::publishsignal(this,SIGNAL(updateleader(double,double,double))
                                                                       ,"Leaderstateupdatesig",Qt::QueuedConnection);
        swarm_Target_Incept_with_obs_avoidenceActivator::publishsignal(this,SIGNAL(LeaderBroadcast(Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd))
                                                                       ,"LeaderBroadCast",Qt::DirectConnection);
    }
    if(order==2)//也就是本机为follower
    {
        swarm_Target_Incept_with_obs_avoidenceActivator::subscribeslot(this,
                                                                       SLOT(Broadcastupdate(Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd))
                                                                       ,"LeaderBroadCast",
                                                                       Qt::DirectConnection);
    }
}

SwarmAgent *vehicle::clone_agent()
{
    vehicle *new_vehicle=new vehicle;
    return new_vehicle;
}

Eigen::MatrixXd vehicle::state_space_equation()
{
    if(ID<agentnum)
    {
        Eigen::MatrixXd d_state;
        d_state.resize(4,1);
        d_state.setZero();
        d_state(0,0)=state_vector(2,0);
        d_state(1,0)=state_vector(3,0);
        d_state(2,0)=act_vector(0,0);
        d_state(3,0)=act_vector(1,0);
        return d_state;
    }
    else
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



    //    if(ID==1 && steps<1000)
    //    {
    //        M_logger->log(steps,0,pos_xy(0,0));
    //        M_logger->log(steps,1,pos_xy(1,0));
    //        M_logger->log(steps,2,vel_xy(0,0));
    //        M_logger->log(steps,3,vel_xy(1,0));

    //        if(steps==999)
    //        {
    //            M_logger->savexlsfile();
    //        }

    //    }
    //    steps++;

}

void vehicle::Broadcastupdate(Eigen::MatrixXd e_t, Eigen::MatrixXd v_t, Eigen::MatrixXd v_n)
{
    m_e_T=e_t;
    m_v_T=v_t;
    m_v_n=v_n;
}
