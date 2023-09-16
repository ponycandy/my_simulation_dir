#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "xmlcore.h"
#include <cmath>
#include <MyMath/MyMathLib.h>
#include <swarm_ETM_compareActivator.h>.h>
// Define pi as a constant
Eigen::MatrixXd originalvector;
int counter=0;

inline double ValueOperator(Eigen::MatrixXd value)
{
    return abs(calculateAngleBetweenVectors(originalvector,value));
}

vehicle::vehicle():SwarmAgent()
{
    cacheSigma=1;
    sigma=cacheSigma;
    cacheOBSclpnum=0;
    status_num=4;
    action_num=2;

    TriggerEvent();
    //动力学不变

    m_e_T.resize(2,1);
    m_e_T.setZero();
    m_v_T.resize(2,1);
    m_v_T.setZero();
    m_v_n=m_v_T;
    leader_act_temp=m_v_T;
    leader_pos_temp=m_v_T;
    leader_vel_temp=m_v_T;

    predictedN=20;

}


void vehicle::state_update()
{
    //状态变量,x,y,vx,vy控制变量ax ay
    if(ID<agentnum)
    {
        pos_xy(0,0)=state_vector(0,0);
        pos_xy(1,0)=state_vector(1,0);
        vel_xy(0,0)=state_vector(2,0);
        vel_xy(1,0)=state_vector(3,0);
        heading_angle=get_angle(vel_xy(0,0),vel_xy(1,0));
        selfETM=state_vector;
    }
    else

    {
        heading_angle=normalize( state_vector(2,0));
        state_vector(2,0)=heading_angle;
        pos_xy(0,0)=state_vector(0,0);
        pos_xy(1,0)=state_vector(1,0);
        vel_xy(0,0)=act_vector(0,0)*cos(heading_angle);
        vel_xy(1,0)=act_vector(0,0)*sin(heading_angle);
        selfETM<<pos_xy(0,0),pos_xy(1,0),vel_xy(0,0),vel_xy(1,0);
    }


    //    TriggerEvent();


}

void vehicle::sensorfunction()
{
    Eigen::MatrixXd greystates;
    greystates.resize(4,1);greystates.setZero();
    if(ID<agentnum)
    {
        double error=0;
        if(cacheOBSclpnum==obs_closet_point_num)
        {

            //计算综合误差

            Eigen::MatrixXd *ETMstate;
            //第一步，使用灰度估计的还是上一时刻的？后者可能会导致
            //触发过于频繁，但是编程比较方便，先使用后者吧：上一次触发的
            for(int j=1;j<=neib_num+1;j++)//遍历所有的相邻者，其实这一步不太严谨，毕竟neib是按照真实neib来判断的
            {
                //此外，还需要包括目标，否则纯追踪目标的时候，误差很大

                ETMstate=ETM_sensor.value(j);//目标也放在ETMstate里面，不同的是，目标的更新是实时的
                if(nearbyagentdistance.contains(j))
                {
                    if(ETM_Flag[j]==1)
                    {
                        //直接使用最新状态,但是，需要将这个状态roll进去
                        predictguy[j]->GetreturnState(greystates,*ETMstate);
                        Cachegrey[j]=greystates;
                        //          predictguy[j]->ClearIterate();
                        //                        predictguy[j]->GetReturnQue(greystates,*ETMstate);
                        //                        predictguy[j]->QueuInsert(*ETMstate);
                        //                        predictguy[j]->predictOnce(greystates);//写入A和B
                        //                        predictguy[j]->clearsteps();
                        //                        predictguy[j]->dorandomthings();
                        //奇怪，这里面混杂了什么数据？
                        //这里是所有agent的数据！
                        for(int ko=0;ko<=3;ko++)
                        {
                            //                            if(ETMstate->coeffRef(ko,0)==0)
                            //                            {
                            //                                qDebug()<<"error";
                            //                            }
                            logger->log(internalcount,4*j+ko,ETMstate->coeffRef(ko,0));
                        }

                    }
                    else
                    {
                        //灰度预测
                        //                        if(internalcount==220 && j==2)
                        //                        {
                        //                            qDebug()<<"error!";
                        //                        }
                        Eigen::MatrixXd matcache=Cachegrey[j];
                        //假设上一步是更新步，那这一步就直接取上一次的预测值
                        //                        predictguy[j]->IteratePredict(greystates);
                        predictguy[j]->GetreturnState(greystates,matcache);
                        //                         predictguy[j]->GetreturnState(greystates,*ETMstate);
                        //这个ETMstate并不是上一个预测时长内的预测结果
                        //而是每次都是全新的，这样当然会出问题
                        ETMstate=&matcache;
                        //速度预测问题非常大
                        //可是fuck，怎么找bug呢
                        //                        ETMstate=&greystates;
                        //得把数据塞回到ETM_sensor里面，确保下次取的是预测数据
                        Cachegrey[j]=greystates.eval();


                        for(int ko=0;ko<=3;ko++)
                        {
                            //                            if(ETMstate->coeffRef(ko,0)==0)
                            //                            {
                            //                                qDebug()<<"error";
                            //                            }
                            logger->log(internalcount,4*j+ko,ETMstate->coeffRef(ko,0));
                        }
                        //灰色状态


                    }

                    //这个差值非常小，说明工作状态良好！
                    double c1=0.1;
                    double distance=nearbyagentdistance.value(j);
                    Eigen::MatrixXd n_ij=ETM_sensor.value(j)->block(0,0,2,1)-pos_xy;
                    double norm_2=n_ij.norm();
                    error+=c1*pow(norm_2-distance,2);
                }

                Eigen::MatrixXd n_ij=ETM_sensor.value(j)->block(2,0,2,1)-vel_xy;
                double norm_2=n_ij.norm();
                double c2=0.1;
                error+=c2*pow(norm_2,2);

            }
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
            double fault=(state_vector-ETM_sensor.value(ID)->eval()).norm()-sigmatemp*state_vector.norm();
            if(fault>0)
            {
                TriggerEvent();
                cacheSigma=sigmatemp;
            }
            else
            {
                //不触发

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
        emit LeaderBroadcast(pos_xy,vel_xy,vel_xy,vel_xy);
        emit updatetarget(pos_xy(0,0),pos_xy(1,0),heading_angle);
        TriggerEvent();
    }
    if(ETMflag==1)
    {
        logger->log(internalcount,0,pos_xy(0,0));logger->log(internalcount,1,pos_xy(1,0));logger->log(internalcount,2,vel_xy(0,0));logger->log(internalcount,3,vel_xy(1,0));
        //触发状态
    }
    else
    {
        logger->log(internalcount,0,0);logger->log(internalcount,1,0);logger->log(internalcount,2,0);logger->log(internalcount,3,0);
        //非触发状态
    }
    logger->log(internalcount,4*(agentnum)+0,pos_xy(0,0));
    logger->log(internalcount,4*(agentnum)+1,pos_xy(1,0));
    logger->log(internalcount,4*(agentnum)+2,vel_xy(0,0));
    logger->log(internalcount,4*(agentnum)+3,vel_xy(1,0));
    //真实状态

    if(internalcount>1200)
    {
        logger->savexlsfile();
    }
    internalcount++;
}

void vehicle::broadcastfunction()
{
}

void vehicle::controlfunction()
{
    Eigen::MatrixXd n_ij;n_ij.resize(2,1);n_ij.setZero();

    Eigen::MatrixXd grad;
    grad=n_ij;
    Eigen::MatrixXd grad1;
    grad1=n_ij;
    Eigen::MatrixXd gradient_term;gradient_term=n_ij;
    Eigen::MatrixXd concencus;concencus=n_ij;
    Eigen::MatrixXd chasing_term;chasing_term=n_ij;




    Eigen::MatrixXd vec_4d;
    vec_4d.resize(4,1);
    vec_4d.setZero();
    Eigen::MatrixXd *ETMstate;

    //遍历ETM，这里假设ETM就是全部neib

    //这里还是不行啊
    //但是我有一个新的想法了，初始化的时候全部定死就行了
    Eigen::MatrixXd avergae_vel;
    avergae_vel.resize(2,1);
    avergae_vel.setZero();
    int jnum=1;
    avergae_vel=vel_xy;
    if(ID<agentnum)
    {
        for(int j=1;j<=neib_num+1;j++)//假设最后一个是target，要追踪最后一个
        {
            if(j!=ID)
            {
                ETMstate=ETM_sensor.value(j);//目标也放在ETMstate里面，不同的是，目标的更新是实时的
                //必须除开自己
                if(nearbyagentdistance.contains(j))//这个是relation_matrix
                {
                    double distance=nearbyagentdistance.value(j);
                    avergae_vel+=ETMstate->block(2,0,2,1);
                    Eigen::MatrixXd n_ij=ETMstate->block(0,0,2,1)-pos_xy;
                    concencus+=ETMstate->block(2,0,2,1)-vel_xy;
                    double norm_2=n_ij.norm();
                    //                    qDebug()<<norm_2-distance;

                    Eigen::MatrixXd grad=(norm_2-distance)*n_ij.normalized();
                    //这里的插值必须选择为一个给定的小于通讯半径的值，我们总是选择0.5*communication_range
                    //当然，这个距离可以被设计用来编队
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

            vel_mag=(m_v_T+vel_xy).norm();
            edge0.normalize();//vel of beta ganet
            beta_agent_control=vel_mag*edge0;//vel of beta ganet
            close_agent->angle=get_angle(beta_agent_control(0,0),beta_agent_control(1,0));
            norm=beta_agent_control-vel_xy;
            concencus=concencus+norm;
            norm=pos_close_agent-pos_xy;
            dot=norm.norm();
            grad=(dot-communication_range)/pow(dot,2)*norm;

            Eigen::MatrixXd n_i_j_hat=(posofcp-pos_xy)/sqrt(1+yip*pow((posofcp-pos_xy).norm(),2));
             gradient_term=gradient_term+phibeta((posofcp-pos_xy).norm())*n_i_j_hat;
//            gradient_term=gradient_term+grad;
        }
        act_vector=act_vector+(concencus+0.55*gradient_term);
        return;
    }
    if(ID==agentnum)
    {

        act_vector<<1,0.1;//目标轨迹形成点
        if(internalcount>800)
        {
            act_vector.setZero();
        }

        return;
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
    //这一步在Getlookaheadpoint完成了

}

void vehicle::Getlookaheadpoint()
{

}
void vehicle::setsendsig(int order)
{


    qRegisterMetaType<Eigen::MatrixXd>("Eigen::MatrixXd");
    if(order==0)//也就是本机为target
    {
        swarm_ETM_compareActivator::publishsignal(this,SIGNAL(updatetarget(double,double,double))
                                          ,"Targetstateupdatesig",Qt::QueuedConnection);
        swarm_ETM_compareActivator::publishsignal(this,SIGNAL(LeaderBroadcast(Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd))
                                          ,"LeaderBroadCast",Qt::DirectConnection);
    }
    if(order==1)//也就是本机为agent
    {
        Eigen::MatrixXd MatHistory;
        MatHistory.resize(4,predictedN);
        predictguy.resize(agentnum+1);
        Cachegrey.resize(agentnum+1);
        for(int j=1;j<=agentnum;j++)
        {

            GrayAray *newgut=new GrayAray;
            predictguy[j]=newgut;//从0开始
            MatHistory.setZero();
            predictguy[j]->resize(4);
            predictguy[j]->storeInitial(MatHistory);
            //            predictguy[j]->setMaxqueue(predictedN,4);
            Eigen::MatrixXd newmat;
            newmat.resize(4,1);
            newmat.setZero();
            Cachegrey[j]=newmat;
        }



        swarm_ETM_compareActivator::subscribeslot(this,SLOT(Broadcastupdate(Eigen::MatrixXd,Eigen::MatrixXd,Eigen::MatrixXd))
                                          ,"LeaderBroadCast",
                                          Qt::DirectConnection);
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
}

void vehicle::Broadcastupdate(Eigen::MatrixXd e_t, Eigen::MatrixXd v_t, Eigen::MatrixXd v_n, Eigen::MatrixXd othersignal)
{
    //接受数据为目标的位置，速度
    m_e_T=e_t-pos_xy;//得出相对于自身的相对坐标
    m_v_T=v_t-vel_xy;//得出相对于自身的相对速度
    m_v_n=v_n;//没用
    leader_act_temp=othersignal;//没用
}
double vehicle::sigmanorm(Eigen::MatrixXd &vec)
{
    return 1/yip*(-1+sqrt(1+yip*pow(vec.norm(),2)));
}

double vehicle::sigma_1_norm(double value)
{
    return 1/sqrt(1+pow(value,2));
}

double vehicle::phibeta(double normnow)
{
    return nuoh(normnow/dbeta)*(sigma_1_norm(normnow-dbeta)-1);
}

double vehicle::nuoh(double value)
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
