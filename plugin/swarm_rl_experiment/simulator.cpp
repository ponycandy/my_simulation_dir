#include "simulator.h"
#include <QElapsedTimer>
#include <QCoreApplication>
#include "swarm_rl_experimentActivator.h"
#include "QtDebug"
Simulator::Simulator(QObject *parent)
{

}

void Simulator::randonize_obs()
{
    if(obs_num>0)


    {

        single_obstacle *obs=obsbounding_group.value(1);
        obs->vertex_num=4;
        obs->vertex_map<<QPointF(5,5)<<QPointF(10,0)<<QPointF(5,-5)<<QPointF(3,-5);


        obs->x_up=13;
        obs->x_low=-5;
        obs->y_up=8;
        obs->y_low=-8;

        //    这一部分复用：可以考虑读取xml文件，做一个这样的读取器，不仅适用于读取障碍物，还适用于其它xml文件
        //    理想的API是：openfile(xxxx.xml)
        //               qstring name=getproperty("property name")//然后会自动寻找这一条属性，并返回其值

    }

}

void Simulator::update_obs()
{
    emit sig_obs_state_update(obsbounding_group);

}

double Simulator::get_angle(double vx, double vy)
{
    double value=0;
    if(vx==0 && vy==0)
    {
        return value;
    }
    else
    {
        value=atan2(vy,vx);
        return  value;
    }
}

void Simulator::init()

{
    m_service=swarm_rl_experimentActivator::getService<CollisionDetectservice>("CollisionDetectservice");
    delta_t=30;
    agent_num=6;
    obs_num=1;
    for(int i=1;i<=obs_num;i++)
    {
        single_obstacle *new_obs=new single_obstacle;
        new_obs->ID=i;
        obsbounding_group.insert(i,new_obs);
    }
    for(int i=1;i<=agent_num;i++)
    {
        Single_agent *new_agent=new Single_agent;
        new_agent->ID=i;
        new_agent->communication_range=5;
        new_agent->collision_r=3;
        Agents_group.insert(i,new_agent);
    }
    state_array.resize(agent_num,5);
    act_array.resize(agent_num,2);
    act_array.setZero();
    state_array.setZero();
    randonize_state();
    randonize_obs();
    Amat.resize(4,4);
    delta_t=30;
    Amat << 0.0, 0.0, 1.0, 0.0,
            0.0,0.0, 0.0, 1.0,

            0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0;
    Bmat.resize(4,2);
    Bmat << 0.0,0.0,
            0.0,0.0,
            1.0,0.0,
            0.0,1.0;
    neib_array.resize(agent_num,agent_num);
    agent_communication_range=Agents_group.value(1)->communication_range;
    collision_r=Agents_group.value(1)->collision_r;
}
void Simulator::randonize_state()
{
    srand(int(time(NULL)));

    for(int i=1;i<=agent_num;i++)
    {
        int num=rand()%99;
        int num1=rand()%98;
        Agents_group.value(i)->state(0,0)=num/100-5-i;
        Agents_group.value(i)->state(1,0)=num1/100-5-i;
//        Agents_group.value(2)->state(0,0)=3;
//        Agents_group.value(2)->state(1,0)=1;
//        Agents_group.value(3)->state(0,0)=3;
//        Agents_group.value(3)->state(1,0)=3;

                qDebug()<<Agents_group.value(i)->state(0,0);
                qDebug()<<Agents_group.value(i)->state(1,0);
        QElapsedTimer et;
        et.start();
        while(et.elapsed()<100)//ms
        {
            QCoreApplication::processEvents();
        }
    }
}
void Simulator::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    for(int i=1;i<=agent_num;i++)
    {
        Single_agent *agent=Agents_group.value(i);
        agent->state=agent->state+0.001*delta_t*(Amat*agent->state+Bmat*agent->act);
        state_array(i-1,0)=agent->state(0,0);state_array(i-1,1)=agent->state(1,0);
        state_array(i-1,2)=agent->state(2,0);state_array(i-1,3)=agent->state(3,0);
        agent->vel(0,0)=agent->state(2,0); agent->vel(1,0)=agent->state(3,0);
        agent->pos(0,0)=agent->state(0,0); agent->pos(1,0)=agent->state(1,0);
        if(state_array(i-1,3)==0 && state_array(i-1,2)==0)
        {
            //do nothing
        }
        else
        {
            agent->angle= atan2(state_array(i-1,3), state_array(i-1,2));
        }

        //        state_array(i-1,4)=agent->state(3,1)/agent->state(2,1);这个暂时为空吧，计算反三角函数
        //还是比较费劲的
        //一般来说，配合以上东西制作一个array解释器，否则就要像上面一样手动选取值
    }

}

void Simulator::control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat)
{
    double  concencus_x=0;
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
    Eigen::MatrixXd concencus;
    concencus.resize(2,1);
    Eigen::MatrixXd chasing_term;
    chasing_term.resize(2,1);

    Eigen::MatrixXd target_state;
    target_state.resize(4,1);
    target_state<<13.0,
            3.0,
            0.0,
            0.0;

    Eigen::MatrixXd vec_4d;
    vec_4d.resize(4,1);
    vec_4d.setZero();

    for(int i=1;i<=agent_num;i++)
    {
        concencus_x=0;gradient_term_x=0;
        concencus_y=0;gradient_term_y=0;
        Single_agent *agent=Agents_group.value(i);
        gradient_term.setZero();
        for(int j=1;j<=agent->neib_num;j++)
        {
            Single_agent *neib_agent=agent->neib_map.value(j);
            concencus_x=concencus_x+neib_agent->state(2,0)-agent->state(2,0);
            concencus_y=concencus_y+neib_agent->state(3,0)-agent->state(3,0);
            norm_2=(pow((neib_agent->state(0,0)-agent->state(0,0)),2)
                    +pow((neib_agent->state(1,0)-agent->state(1,0)),2));
            norm_2=sqrt(norm_2);
            Eigen::MatrixXd n_m_ij=neib_agent->state-agent->state;
            n_ij(0,0)=n_m_ij(0,0);n_ij(1,0)=n_m_ij(1,0);

            grad=(norm_2-neib_agent->communication_range)/pow(norm_2,2)*n_ij;
            gradient_term=gradient_term+grad;

        }
        concencus(0,0)=concencus_x;concencus(1,0)=concencus_y;
        vec_4d=agent->state-target_state;
        grad(0,0)=vec_4d(0,0);grad(1,0)=vec_4d(1,0);
        grad1(0,0)=vec_4d(2,0);grad1(1,0)=vec_4d(3,0);

        chasing_term=-0.3*grad-0.1*grad1;
        agent->act=(concencus+gradient_term+chasing_term);

        double dot=0; double vel_mag;
        Eigen::MatrixXd edge0;  Eigen::MatrixXd norm;
        Eigen::MatrixXd edge1;  Eigen::MatrixXd edge2;
        Eigen::MatrixXd beta_agent_control;
        beta_agent_control.resize(2,1);   norm.resize(2,1);
        beta_agent_control.setZero();gradient_term.setZero();
        edge0=beta_agent_control;edge1=edge0=edge2=edge0;
        concencus.setZero();
        Eigen::MatrixXd pos_close_agent=edge0;
        for(int j=1;j<=agent->obs_closet_point_num;j++)
        {
            pos_xy close_agent=agent->closepoint_map.value(j);


            edge1(0,0)=close_agent.edge1_x;
            edge1(1,0)=close_agent.edge1_y;

            edge2(0,0)=close_agent.edge2_x;
            edge2(1,0)=close_agent.edge2_y;

            pos_close_agent(0,0)=close_agent.x;
            pos_close_agent(1,0)=close_agent.y;

            dot=agent->state(2,0)*edge1(0,0)+agent->state(3,0)*edge2(1,0);
            if(dot>=0)
            {
                edge0=edge1;
            }
            else
            {
                edge0=edge2;
            }
            vel_mag=agent->vel.norm();
            edge0.normalize();//vel of beta ganet
            beta_agent_control=-vel_mag*edge0;//vel of beta ganet
            close_agent.angle=get_angle(beta_agent_control(0,0),beta_agent_control(1,0));
            norm=beta_agent_control-agent->vel;
            concencus=concencus+norm;
            norm=pos_close_agent-agent->pos;dot=norm.norm();
            grad=(dot-agent->communication_range)/pow(dot,2)*norm;
            gradient_term=gradient_term+grad;
        }
        agent->act=agent->act+(concencus+5*gradient_term);



    }
}
void Simulator::sensor(Eigen::MatrixXd state_mat)
{
    detect_neibor(state_array);
    detect_collision();

}

void Simulator::broad_cast(Eigen::MatrixXd state_mat, Eigen::MatrixXd act_mat, Eigen::MatrixXd sensor)
{
    emit sig_agent_state_update(Agents_group);
}
void Simulator::detect_neibor(Eigen::MatrixXd state_mat)
{
    double dis=0;
    neib_array.setZero();
    for(int i=1;i<=agent_num;i++)
    {
        Agents_group.value(i)->remove_all_neibor();
    }
    for(int iter1=1;iter1<=agent_num;iter1++)
    {
        for(int iter2=1;iter2<iter1;iter2++)
        {
            dis=pow(Agents_group.value(iter1)->state(0,0)-Agents_group.value(iter2)->state(0,0),2)
                    +pow(Agents_group.value(iter1)->state(1,0)-Agents_group.value(iter2)->state(1,0),2);
            if(dis<pow(Agents_group.value(iter1)->communication_range,2))
            {
                neib_array(iter1-1,iter2-1)=1;
                neib_array(iter2-1,iter1-1)=1;
                Agents_group.value(iter1)->appendNeibor(Agents_group.value(iter2));
                Agents_group.value(iter2)->appendNeibor(Agents_group.value(iter1));

            }

        }
    }

}
bool Simulator::within_range(Eigen::MatrixXd state, single_obstacle *obs)
{
    if(state(0,0)<obs->x_low ||  state(0,0)>obs->x_up || state(1,0)<obs->y_low ||  state(1,0)>obs->y_up)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void Simulator::detect_collision()
{


    for(int i=1;i<=agent_num;i++)
    {
        Eigen::MatrixXd agent_i_state=Agents_group.value(i)->state;
        Agents_group.value(i)->remove_all_closepoint();
        for(int j=1;j<=obs_num;j++)
        {
            single_obstacle *obs=obsbounding_group.value(j);
            if(within_range(agent_i_state,obs)==1)
            {
                collison_result result=m_service->polygen_circle_detect(agent_i_state(0,0),agent_i_state(1,0),Agents_group.value(i)->collision_r,obs->vertex_map);
                if(result.flag==1)
                {
                    Single_agent* as=Agents_group.value(i);
                    result.closest_point.obs_ID=j;
                    as->append_closepointpair(j,result.closest_point);
                    //Eigen probelm
                }
            }
            else
            {

            }
        }

    }

}
