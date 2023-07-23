#include "SwarmAgent.h"

SwarmAgent::SwarmAgent()
{

    pos_xy.resize(2,1);
    pos_xy.setZero();
    vel_xy.resize(2,1);
    vel_xy.setZero();
    neib_num=0;
    sensor_subject_num=0;
    obs_closet_point_num=0;
}

void SwarmAgent::appendNeibor(SwarmAgent *agent, double dis)
{
    neib_num+=1;
    neib_map.insert(neib_num,agent);  //一般按照从近到远的顺序append
    neib_Map_distance.insert(neib_num,dis);
}

void SwarmAgent::appendsensorsubject(SwarmAgent *agent)
{
    sensor_subject_num+=1;
    sensor_subject_map.insert(sensor_subject_num,agent);  //一般按照从近到远的顺序append
}

void SwarmAgent::remove_all_closepoint()
{
    for(int it=1;it<=obs_closet_point_num;it++)
    {
        closepoint_map.remove(it);
    }
    obs_closet_point_num=0;
}

void SwarmAgent::sorting()
{
    for(int it=1;it<=neib_num;it++)
    {
        for(int jt=1;jt<=neib_num;jt++)
        {
            if(neib_Map_distance.value(jt)<neib_Map_distance.value(jt+1))
            {
                continue;
            }
            else
            {
                swap(jt,jt+1);
            }
        }
    }
}

void SwarmAgent::swap(int order1, int order2)
{
    double middis=0;
    middis=neib_Map_distance.value(order1);
    neib_Map_distance[order1]=neib_Map_distance.value(order2);
    neib_Map_distance[order2]=middis;

    SwarmAgent *middia=neib_map.value(order1);
    neib_map[order1]=neib_map.value(order2);
    neib_map[order2]=middia;
}

void SwarmAgent::remove_all_neibors()
{
    for(int it=1;it<=neib_num;it++)
    {
        neib_map.remove(it);
        neib_Map_distance.remove(it);
    }
    neib_num=0;
}

void SwarmAgent::remove_all_sensorsubject()
{
    for(int it=1;it<=sensor_subject_num;it++)
    {
        sensor_subject_map.remove(it);
    }
    sensor_subject_num=0;
}

void SwarmAgent::append_closepointpair(int j, ClosePoint *closest)
{
    obs_closet_point_num++;
    closepoint_map.insert(obs_closet_point_num,closest);
}
