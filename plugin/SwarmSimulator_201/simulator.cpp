#include "simulator.h"
#include <QElapsedTimer>
#include <QCoreApplication>
#include "SwarmSimulator_201Activator.h"
#include "QtDebug"
Simulator::Simulator(QObject *parent)
{
    m_service=SwarmSimulator_201Activator::getService<CollisionDetectservice>("CollisionDetectservice");
    neib_seq=0;
}
void Simulator::update_obs()
{
    emit sig_obs_state_update(obsbounding_group);

}

void Simulator::init(int ID)
{

    thread_ID=ID;
    update_obs();
}
void Simulator::ode_function(Eigen::MatrixXd act_mat, Eigen::MatrixXd state_mat)
{
    for(int i=1;i<=agent_num;i++)
    {
        SwarmAgent *agent=Agents_group.value(i);
        agent->state_vector=agent->state_vector+0.001*delta_t*agent->state_space_equation();
        agent->state_update();
    }
}

void Simulator::control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat)
{
    for(int i=1;i<=agent_num;i++)
    {
        SwarmAgent *agent=Agents_group.value(i);
        agent->controlfunction();
    }
}
void Simulator::sensor(Eigen::MatrixXd state_mat)
{
    detect_neibor(state_array);
    detect_collision();
    //系统完成默认服务：碰撞检测和邻居识别，然后进入agent环节
    for(int i=1;i<=agent_num;i++)
    {
        SwarmAgent *agent=Agents_group.value(i);
        agent->sensorfunction();
    }
    for(int i=1;i<=agent_num;i++)
    {
        SwarmAgent *agent=Agents_group.value(i);
        for(int j=1;j<=agent_num;j++)
        {
            agent->ETM_Flag[j]=0;
        }
    }
    //上面过程完成后，agent自行选择是否触发自己的数据传感，然后再在
    //下面进行ETM传感数据的检测
    for(int i=1;i<=agent_num;i++)
    {
        SwarmAgent *agent=Agents_group.value(i);
        if(agent->ETMflag==1)
        {
            //各agent关于自己的ETM用来存储上一次广播的state
            *(agent->ETM_sensor[agent->ID])=(&(agent->selfETM))->eval();
            QMap<int, SwarmAgent *>::const_iterator iter2 = agent->neib_map.cbegin();
            //遍历，将所有这个agent的邻居的ETM状态给更新

            while (iter2 != agent->neib_map.cend())
            {
                *(iter2.value()->ETM_sensor[agent->ID])=
                    (&(agent->selfETM))->eval();
                //拷贝对应对象的最新状态
                iter2.value()->ETM_Flag[agent->ID]=1;//提示状态触发，这部分总是事先清0
                //
                ++iter2;
                //ETM_vec和ETM_sensor自行根据需求选取
            }
            agent->ETMflag=0;
        }
    }
}

void Simulator::broad_cast(Eigen::MatrixXd state_mat, Eigen::MatrixXd act_mat, Eigen::MatrixXd sensor)
{
    emit sig_agent_state_update(Agents_group);
    for(int i=1;i<=agent_num;i++)
    {
        SwarmAgent *agent=Agents_group.value(i);
        agent->broadcastfunction();
    }
}
void Simulator::detect_neibor(Eigen::MatrixXd state_mat)
{

    double dis=0;
    for(int i=1;i<=agent_num;i++)
    {
        Agents_group.value(i)->remove_all_neibors();
        Agents_group.value(i)->remove_all_sensorsubject();
    }
    for(int iter1=1;iter1<=agent_num;iter1++)
    {
        for(int iter2=1;iter2<iter1;iter2++)
        {
            dis=pow(Agents_group.value(iter1)->pos_xy(0,0)-Agents_group.value(iter2)->pos_xy(0,0),2)
                  +pow(Agents_group.value(iter1)->pos_xy(1,0)-Agents_group.value(iter2)->pos_xy(1,0),2);
            if(dis<pow(Agents_group.value(iter1)->communication_range,2) && dis<pow(Agents_group.value(iter2)->communication_range,2))
            {
                //这里需要两种判断：1.感知判断，添加appendsensor  2.真实通讯判断，添加appendneibor
                // 3.触发通讯判断，添加appendETM，以后还有额外的图，都通过这种范式来添加
                Agents_group.value(iter1)->appendNeibor(Agents_group.value(iter2),dis);
                Agents_group.value(iter2)->appendNeibor(Agents_group.value(iter1),dis);
                //一般认为，只有满足双向连接的通讯才可以作为邻居
                //不然就会默认：感知=通讯，将会无法适用于目标追踪
            }
            if(dis<pow(Agents_group.value(iter1)->sensor_range,2))
            {
                Agents_group.value(iter1)->appendsensorsubject(Agents_group.value(iter2));
            }
            if(dis<pow(Agents_group.value(iter2)->sensor_range,2))
            {
                Agents_group.value(iter2)->appendsensorsubject(Agents_group.value(iter1));
            }

        }
    }
    if(neib_seq==1)
    {
        //we will first seq the neib according to distance here
        for(int i=1;i<=agent_num;i++)
        {
            Agents_group.value(i)->sorting();
        }
    }


}
bool Simulator::within_range(Eigen::MatrixXd posxy, SwarmObstacle *obs)
{
    if(posxy(0,0)<obs->x_low ||  posxy(0,0)>obs->x_up || posxy(1,0)<obs->y_low ||  posxy(1,0)>obs->y_up)
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
        Agents_group.value(i)->remove_all_closepoint();
        for(int j=1;j<=obs_num;j++)
        {
            SwarmObstacle *obs=obsbounding_group.value(j);
            if(within_range(Agents_group.value(i)->pos_xy,obs)==1)
            {
                collison_result result=m_service->polygen_circle_detect(Agents_group.value(i)->pos_xy(0,0),
                                                                          Agents_group.value(i)->pos_xy(1,0),Agents_group.value(i)->collision_r,obs->vertex_map);
                if(result.flag==1)
                {
                    //一般都将collision range设置为communiaction range，涉及到的假设就是，无人车
                    //之间只能用视觉传感器感知对方，所以collisionr和communication_r是一样的
                    //当让，也存在collision_r小于communication_r的情况
                    //但是，一般不考虑无人车之间的碰撞
                    SwarmAgent* as=Agents_group.value(i);
                    result.closest_point.obs_ID=j;
                    ClosePoint *a_point=new ClosePoint;
                    a_point->x=result.closest_point.x;
                    a_point->y=result.closest_point.y;
                    a_point->obs_ID=result.closest_point.obs_ID;
                    a_point->edge1_x=result.closest_point.edge1_x;
                    a_point->edge1_y=result.closest_point.edge1_y;
                    a_point->edge2_x=result.closest_point.edge2_x;
                    a_point->edge2_y=result.closest_point.edge2_y;
                    a_point->next_vertex=result.closest_point.next_vertex;
                    a_point->last_vertex=result.closest_point.last_vertex;
                    a_point->update_state();

                    as->append_closepointpair(j,a_point);
                    //Eigen probelm
                }
            }
            else
            {

            }
        }

    }

}
