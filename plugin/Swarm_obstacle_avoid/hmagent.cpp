#include "hmagent.h"
#include "xmlcore.h"
HMagent::HMagent(QObject *parent)
    : QObject{parent}
{
    xmlCore xmlreader("./config/swarm/predict.xml");
    status_num=4;
    action_num=2;
    heading_angle=0;
    target_state.resize(4,1);
    xmlreader.xmlRead("Gamastate",target_state);
    xmlreader.xmlRead("communication_range",communication_range);
    xmlreader.xmlRead("collision_r",collision_r);

}

double HMagent::get_angle(double vx, double vy)
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
void HMagent::state_update()
{
    //状态变量,x,y,vx,vy控制变量ax ay
    heading_angle=state_vector(2,0);
    pos_xy(0,0)=state_vector(0,0);
    pos_xy(1,0)=state_vector(1,0);
    vel_xy(0,0)=state_vector(2,0);
    vel_xy(1,0)=state_vector(3,0);
    heading_angle=get_angle(vel_xy(0,0),vel_xy(1,0));
}

void HMagent::sensorfunction()
{

}

void HMagent::broadcastfunction()
{

}

void HMagent::controlfunction()
{
    //下面是原版算法
    double concencus_x=0;
    double concencus_y=0;
    double gradient_term_x=0;
    double gradient_term_y=0;
    double norm_2=0;
    Eigen::MatrixXd n_ij;
    n_ij.resize(2,1);
    Eigen::MatrixXd grad;
    grad.resize(2,1);

    Eigen::MatrixXd grad1;
    grad1.resize(2,1);
    Eigen::MatrixXd gradient_term;
    gradient_term.resize(2,1);
    gradient_term.setZero();
    Eigen::MatrixXd concencus;
    concencus.resize(2,1);
    Eigen::MatrixXd chasing_term;
    chasing_term.resize(2,1);



    Eigen::MatrixXd vec_4d;
    vec_4d.resize(4,1);
    vec_4d.setZero();



    for(int j=1;j<=neib_num;j++)
    {
        SwarmAgent *neib_agent=neib_map.value(j);
        concencus_x=concencus_x+neib_agent->state_vector(2,0)-state_vector(2,0);
        concencus_y=concencus_y+neib_agent->state_vector(3,0)-state_vector(3,0);
        norm_2=(pow((neib_agent->state_vector(0,0)-state_vector(0,0)),2)
                  +pow((neib_agent->state_vector(1,0)-state_vector(1,0)),2));
        norm_2=sqrt(norm_2);
        Eigen::MatrixXd n_m_ij=neib_agent->state_vector-state_vector;
        n_ij(0,0)=n_m_ij(0,0);
        n_ij(1,0)=n_m_ij(1,0);

        grad=(norm_2-neib_agent->communication_range)/pow(norm_2,2)*n_ij;
        gradient_term=gradient_term+grad;
//        QString bug=QString::number(this->ID)+QString("norm is ");
//        qDebug()<<bug<<norm_2;
//        qDebug()<<"neib_agent_vector_downhere";
//        qDebug()<<neib_agent->state_vector(0,0)<<" "<<neib_agent->state_vector(1,0)<<" "<<
//            neib_agent->state_vector(2,0)<<" "<<neib_agent->state_vector(3,0)<<" ";
//        qDebug()<<"self_vector_downhere";
//        qDebug()<<state_vector(0,0)<<" "<<state_vector(1,0)<<" "<<
//            state_vector(2,0)<<" "<<state_vector(3,0)<<" ";
    }
    concencus(0,0)=concencus_x;
    concencus(1,0)=concencus_y;
    vec_4d=state_vector-target_state;
    grad(0,0)=vec_4d(0,0);
    grad(1,0)=vec_4d(1,0);
    grad1(0,0)=vec_4d(2,0);
    grad1(1,0)=vec_4d(3,0);
//    qDebug()<<"vec_4d_downhere";
//    qDebug()<<vec_4d(0,0)<<" "<<vec_4d(1,0)<<" "<<
//        vec_4d(2,0)<<" "<<vec_4d(3,0)<<" ";
    chasing_term=-0.3*grad-0.1*grad1;
    act_vector=(concencus+gradient_term+chasing_term);

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

        dot=state_vector(2,0)*edge1(0,0)+state_vector(3,0)*edge1(1,0);
        //此处需要仔细考虑一下....仿真使用这个精度是不是就够了...这样的速度判断
        //这里就不严格按照论文来了
        if(dot>=0)
        {
            edge0=edge1;
        }
        else
        {
            edge0=edge2;
        }
        vel_mag=vel_xy.norm();
        edge0.normalize();//vel of beta ganet
        beta_agent_control=-vel_mag*edge0;//vel of beta ganet
        close_agent->angle=get_angle(beta_agent_control(0,0),beta_agent_control(1,0));
        norm=beta_agent_control-vel_xy;
        concencus=concencus+norm;
        norm=pos_close_agent-pos_xy;
        dot=norm.norm();
        grad=(dot-communication_range)/pow(dot,2)*norm;
        gradient_term=gradient_term+grad;
    }
    act_vector=act_vector+(concencus+5*gradient_term);
//    if(isnan(act_vector(0,0)) || isnan(act_vector(1,0)))
//    {
//        int a=0;
//    }

}

void HMagent::fault_set(int option)
{

}

SwarmAgent *HMagent::clone_agent()
{
    HMagent *new_vehicle=new HMagent;
    return new_vehicle;
}

Eigen::MatrixXd HMagent::state_space_equation()
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
