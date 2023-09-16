#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "xmlcore.h"
#include "swarm_Target_Incept_with_obs_avoidenceActivator.h"
#include <cmath>

#include <MyMath/MyMathLib.h>

Eigen::MatrixXd originalvector;


inline double ValueOperator(Eigen::MatrixXd value)
{
    return abs(calculateAngleBetweenVectors(originalvector,value));
}



vehicle::vehicle():SwarmAgent()
{
    m_e_T.resize(2,1);
    m_e_T.setZero();
    m_v_T.resize(2,1);
    m_v_T.setZero();
    m_v_n=m_v_T;
    leader_act_temp=m_v_T;
    leader_pos_temp=m_v_T;
    leader_vel_temp=m_v_T;

    QString configfilename="./config/swarmInception/swarm.xml";
    xmlCore Xmlreader(configfilename.toStdString());
    Xmlreader.xmlRead("agent_num",agentnum);
    status_num=4;
    action_num=2;
    int obs_num_now;
    Xmlreader.xmlRead("communication_range",communication_range);
    Xmlreader.xmlRead("collision_r",collision_r);
    Xmlreader.xmlRead("sensor_range",sensor_range);
    Xmlreader.xmlRead("obs_num",obs_num_now);
    heading_angle=0;
    falseflag=0;

    Xmlreader.xmlRead("predicthorizon",predicthorizon);

    steps=0;//用来记录

    leader_act_temp.resize(2,1);
    leader_act_temp.setZero();
    leader_self_act_vector.resize(2,1);
    leader_self_act_vector.setZero();
    m_service=swarm_Target_Incept_with_obs_avoidenceActivator::getService<CollisionDetectservice>("CollisionDetectservice");


    for(int i=1;i<=obs_num_now;i++)
    {
        SwarmObstacle *new_obs=new SwarmObstacle;
        QString obs_term_name="OBS_"+QString::number(i)+"_vertexnum";
        Xmlreader.xmlRead(obs_term_name.toStdString(),new_obs->vertex_num);
        new_obs->ID=i;
        Eigen::MatrixXd obs_mat;
        obs_mat.resize(new_obs->vertex_num,2);
        obs_term_name="OBS_"+QString::number(i)+"_vertexparams";
        std::vector<double> point_x_vec;
        std::vector<double> point_y_vec;
        Xmlreader.xmlRead(obs_term_name.toStdString(),obs_mat);
        for(int j=1;j<=new_obs->vertex_num;j=j+1)
        {
            double x= obs_mat(j-1,0);
            double y= obs_mat(j-1,1);
            point_x_vec.push_back(x);
            point_y_vec.push_back(y);
            new_obs->vertex_map<<QPointF(x,y);
        }

        double max_x = *max_element(point_x_vec.begin(), point_x_vec.end());
        double max_y = *max_element(point_y_vec.begin(), point_y_vec.end());
        double min_x = *min_element(point_x_vec.begin(), point_x_vec.end());
        double min_y = *min_element(point_y_vec.begin(), point_y_vec.end());

        new_obs->x_up=max_x+collision_r;
        new_obs->x_low=min_x-collision_r;
        new_obs->y_up=max_y+collision_r;
        new_obs->y_low=min_y-collision_r;

        obsbounding_group.insert(i,new_obs);
    }
    dbeta=collision_r;

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
    if(ID==1)//for leader
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
                m_v_T=subject->vel_xy-vel_xy;//注意原论文中的vt-un的实际含义，对应这里的m_v_t
            }
        }
        m_v_n=vel_xy;
    }
}

Eigen::MatrixXd vehicle::predict_Collistion(ClosePoint *clagent)
{

    double distance_1=0;
    double distance_2=0;

    //遍历障碍物到leader的cp点
    collison_result result=m_service->polygen_circle_detect(leader_pos_temp(0,0)
                                                              ,leader_pos_temp(1,0),
                                                              100,obsbounding_group.value(clagent->obs_ID)->vertex_map);
    SwarmObstacle *obs=obsbounding_group.value(clagent->obs_ID);
    Eigen::MatrixXd edge;edge.resize(2,1);edge.setZero();
    Eigen::MatrixXd startp;startp=edge;
    Eigen::MatrixXd endp;endp=edge;
    Eigen::MatrixXd Targetp;Targetp=edge;
    Eigen::MatrixXd Currentp;Currentp=edge;
    Targetp<< result.closest_point.x, result.closest_point.y;
    startp=clagent->pos;
    //首先判断目标点位置是不是就在相邻的边上，如果在，那么就不需要后面的过程了
    //第一条边：
    endp<<obs->vertex_map.at(clagent->next_vertex-1).x(),obs->vertex_map.at(clagent->next_vertex-1).y();


    if(Point_on_line(startp,endp,Targetp))
    {
        return Targetp-startp;
    }
    //第二条边
    endp<<obs->vertex_map.at(clagent->last_vertex-1).x(),obs->vertex_map.at(clagent->last_vertex-1).y();
    if(Point_on_line(startp,endp,Targetp))
    {
        return Targetp-startp;
    }
    //上面两个如果都没有返回，说明临近点在更远的位置，就需要做距离积分了
    //下面是增序方向
    endp<<obs->vertex_map.at(clagent->next_vertex-1).x(),obs->vertex_map.at(clagent->next_vertex-1).y();
    //计算第一段长度:
    double firstlength=(endp-startp).norm();
    distance_1+=firstlength;
    //首先是增序方向
    //    for(int i=clagent->next_vertex;i<=obs->vertex_num;i++)
    int i=clagent->next_vertex;
    for(int j=1;j<=obs->vertex_num;j++)
    {
        int head=(i)%obs->vertex_map.length();
        if(head==0)
        {
            head=obs->vertex_map.length();
        }
        int tail=(head+1)%obs->vertex_map.length();
        if(tail==0)
        {
            tail=obs->vertex_map.length();
        }
        startp<<obs->vertex_map.at(head-1).x(),obs->vertex_map.at(head-1).y();
        endp<<obs->vertex_map.at(tail-1).x(),obs->vertex_map.at(tail-1).y();

        //这里需要判断目标点是否在线段上面，要包括端点的状态！
        bool istrue=Point_on_line(startp,endp,Targetp);
        if(istrue==1)
        {
            edge=Targetp-startp;
            distance_1+=edge.norm();
            break;
        }
        else
        {
            edge=endp-startp;
            distance_1+=edge.norm();
        }
        i++;
    }
    //然后是减序列方向
    startp=clagent->pos;
    endp<<obs->vertex_map.at(clagent->last_vertex-1).x(),obs->vertex_map.at(clagent->last_vertex-1).y();
    //计算第一段长度:
    firstlength=(endp-startp).norm();
    distance_2+=firstlength;

    i=clagent->last_vertex;
    for(int j=1;j<=obs->vertex_num;j++)
    {
        int head=abs((i)%obs->vertex_map.length());//不知道负数的表现是啥
        if(head==0)
        {
            head=obs->vertex_map.length();
        }
        int tail=abs((head-1)%obs->vertex_map.length());
        if(tail==0)
        {
            tail=obs->vertex_map.length();
        }
        startp<<obs->vertex_map.at(head-1).x(),obs->vertex_map.at(head-1).y();
        endp<<obs->vertex_map.at(tail-1).x(),obs->vertex_map.at(tail-1).y();

        //这里需要判断目标点是否在线段上面，要包括端点的状态！
        bool istrue=Point_on_line(startp,endp,Targetp);
        if(istrue==1)
        {
            edge=Targetp-startp;
            distance_2+=edge.norm();
            break;
        }
        else
        {
            edge=endp-startp;
            distance_2+=edge.norm();
        }
        i--;

    }
    if(distance_2>distance_1)
    {
        //选择增势方向
        endp<<obs->vertex_map.at(clagent->next_vertex-1).x(),obs->vertex_map.at(clagent->next_vertex-1).y();
        startp=clagent->pos;
        return (endp-startp);
    }
    else
    {
        //选择减小方向
        endp<<obs->vertex_map.at(clagent->last_vertex-1).x(),obs->vertex_map.at(clagent->last_vertex-1).y();
        startp=clagent->pos;
        return (endp-startp);
    }
}


void vehicle::broadcastfunction()
{

    if(ID==agentnum)//如果是Targetagent
    {
        updatetarget(pos_xy(0,0),pos_xy(1,0),heading_angle);
        return;
    }

    if(ID==1)//如果是Leader
    {
        updateleader(pos_xy(0,0),pos_xy(1,0),heading_angle);
        LeaderBroadcast(m_e_T,m_v_T,m_v_n,act_vector);
        //上面的值在感知函数中计算
        return;
    }

}


void vehicle::controlfunction()
{
    if(ID==agentnum)//给目标设置一个合适的运动轨迹,目前绕圈比较好，我们设置vel但是不设置act
    {
        act_vector<<1,0.1;
        //        act_vector.setZero();
        return;
    }
    if(ID==agentnum)
    {
        //这里给一个flag，我们在此做一个整体变形的最优化
    }
    if(ID<=agentnum-1)//领导者可以考虑加入一些人类的先验知识
    {
        int returnflag=0;
        double const ka=0.8;
        Eigen::MatrixXd concencus;
        concencus.resize(2,1);
        concencus.setZero();
        Eigen::MatrixXd gradient_term=concencus;
        Eigen::MatrixXd avergae_pos=concencus;
        Eigen::MatrixXd avergae_vel=concencus;
        avergae_vel+=vel_xy;
        for(int j=1;j<=neib_num;j++)
        {
            SwarmAgent *neib_agent=neib_map.value(j);
//            bool judgeblock=ifcommunication_block(neib_agent->pos_xy,pos_xy);
//            if(judgeblock==false)
//            {
                if(nearbyagentdistance.contains(neib_agent->ID))//这个是relation_matrix
                {
                    double distance=nearbyagentdistance.value(neib_agent->ID);
                    avergae_pos+=neib_agent->pos_xy;
                    avergae_vel+=neib_agent->vel_xy;
                    Eigen::MatrixXd n_ij=neib_agent->pos_xy-pos_xy;
                    concencus+=neib_agent->vel_xy-vel_xy;
                    double norm_2=n_ij.norm();


                    Eigen::MatrixXd grad=(norm_2-distance)/pow(norm_2,2)*n_ij;
                    //这里的插值必须选择为一个给定的小于通讯半径的值，我们总是选择0.5*communication_range
                    //当然，这个距离可以被设计用来编队
                    gradient_term+=grad;
                }
//            }
            if(neib_agent->ID==1)
            {
                //记录领导者传达的自身状态:
                leader_pos_temp=neib_agent->pos_xy;
                leader_vel_temp=neib_agent->vel_xy;

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
        posofcp.setZero();
        grad=posofcp;
        if(counter==43)
        {
            qDebug()<<"here!";
        }
        for(int j=1;j<=obs_closet_point_num;j++)
        {
            ClosePoint *close_agent=closepoint_map.value(j);
            //下面计算最小夹角

            //1.计算关联agent的绝对质心,以及绝对平均速度
            avergae_pos/=neib_num;
            avergae_vel/=(neib_num+1);
            //2.计算平均质心在障碍物上的最近点：

            collison_result result=m_service->polygen_circle_detect(avergae_pos(0,0),
                                                                      avergae_pos(1,0),100,
                                                                      obsbounding_group.value(close_agent->obs_ID)->vertex_map);

            Eigen::MatrixXd TargetCp;TargetCp.resize(2,1);TargetCp.setZero();
            TargetCp<<result.closest_point.x,result.closest_point.y;
            //4.计算最近点之间的连接向量
            //            originalvector.resize(2,1);
            //            originalvector<<result.closest_point.x,result.closest_point.y;
            //            originalvector=originalvector-close_agent->pos;
            originalvector=avergae_vel;
            double vel_mag=vel_xy.norm();
            //5.选取最小夹角
            //情况1：CP在边上，首先需要判断是不是和leader有遮挡
            if (close_agent->edg2==-close_agent->edg1)
            {
                if(ID!=1)//非leader需要进行判断
                {
                    //判断和leader的连线是否被当前obs遮挡，如果不是，则执行下面的步骤
//                    collison_result2 result_0=m_service->polygen_line_segment_detect(pos_xy,leader_pos_temp,obsbounding_group.value(close_agent->obs_ID)->vertex_map);
//                    if(result_0.flag==1)
//                    {
//                        edge0=predict_Collistion(close_agent);
//                        //此时，应当忽略和群体的速度一致性，只保留排斥梯度！
//                        returnflag=1;
//                        vel_mag=leader_vel_temp.norm();
//                    }
//                    else
//                    {


                        std::vector<Eigen::MatrixXd> edges = {close_agent->edg1, close_agent->edg2};
                        edge0=*argmin(edges,ValueOperator);
//                    }
                    //有一个问题，无人机不会沿着障碍物边界走
                    //在断开所有外部关联的时候
                }
                else
                {
                    std::vector<Eigen::MatrixXd> edges = {close_agent->edg1, close_agent->edg2};
                    edge0=*argmin(edges,ValueOperator);
                }
            }
            else
            {
                //情况2：顶点，需要计算四个角度取最小
                std::vector<Eigen::MatrixXd> edges = {close_agent->edg1, close_agent->edg2,
                                                      -close_agent->edg1, -close_agent->edg2};

                edge0=*argmin(edges,ValueOperator);
                //这里必须区分是开入顶点还是开出顶点
                //对于后者，取最小化平均速度没有问题
                //对于前者,则不一样,应当无条件选取距离目标较近的
                if(edge0==(-close_agent->edg1) ||  edge0==-close_agent->edg2)
                {
                    //开出顶点,不做干涉
                }
                else
                {
                    //开入顶点
                    //此时应当减少截断,使用预测算法:
                    if(ID!=1)//非leader需要进行判断
                    {
                        edge0=predict_Collistion(close_agent);
                        //这个项最小化环绕距离;
                    }

                }
            }
            //5.计算一致性和共识性速度


            edge0.normalize();//vel of beta ganet
            beta_agent_control=vel_mag*edge0;//这个速度一直写反了啊.....
            close_agent->angle=get_angle(beta_agent_control(0,0),beta_agent_control(1,0));
            concencus = concencus+beta_agent_control-vel_xy;
            posofcp<<close_agent->x,close_agent->y;
            double dot=(posofcp-pos_xy).norm();
            if(dot<2.5)
            {
                grad=(dot-2.5)/pow(dot,2)*(posofcp-pos_xy);
            }
            else
            {
                grad.setZero();
                concencus.setZero();
            }
            Eigen::MatrixXd n_i_j_hat=(posofcp-pos_xy)/sqrt(1+yip*pow((posofcp-pos_xy).norm(),2));
            //应该将目标距离尽可能设置为碰撞距离！
            //不然会使得物体靠近障碍物，被拉到固定距离
            //也就是说，距离大于collision_r的时候
            //即使发现也不产生推力！
            //            gradient_term=gradient_term+20*phibeta((posofcp-pos_xy).norm())*n_i_j_hat;
            //上面这个很光滑，但是无法把自己挤入到障碍物内部
            gradient_term=gradient_term+grad;
            //上面这个不光滑，但是不会把自己挤入到障碍物中
        }
//        if(returnflag==1)
//        {
//            act_vector=0.5*gradient_term+concencus;
//            //为什么这个没有用？因为betaagent在快速反向？
//            return ;
//        }
        leader_self_act_vector=(concencus+5*gradient_term);
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

        //如果本机是leader，需要将本机的一致控制项广播出去

        if(ID==1)
        {
            //  act_vector-leader_self_act_vector 这是本机的一致项
            LeaderBroadcast(m_e_T,m_v_T,m_v_n,act_vector-leader_self_act_vector);
            //本机控制量只保留目标项和避障项目
            act_vector+=h;


        }
        else
        {
            act_vector+=h;
        }
    }
}

bool vehicle::ifcommunication_block(Eigen::MatrixXd &p1, Eigen::MatrixXd &p2)
{
    for(int j=1;j<=obsbounding_group.count();j++)
    {
        SwarmObstacle *obs=obsbounding_group.value(j);
        collison_result2 result=m_service->polygen_line_segment_detect(p1,p2,obs->vertex_map);
        if(result.flag==1)
        {
            return true;
        }
    }
    return false;

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

void vehicle::Broadcastupdate(Eigen::MatrixXd e_t, Eigen::MatrixXd v_t, Eigen::MatrixXd v_n, Eigen::MatrixXd othersignal)
{
    m_e_T=e_t;
    m_v_T=v_t;
    m_v_n=v_n;
    leader_act_temp=othersignal;
}
