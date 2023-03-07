#include "single_agent.h"

Single_agent::Single_agent()
{
    state.resize(4,1);
    state.setZero();
    act.resize(2,1);
    act.setZero();
    neib_num=0;obs_closet_point_num=0;
}

void Single_agent::appendNeibor(Single_agent *neib)
{
    neib_num+=1;
    neib_map.insert(neib_num,neib);
}

void Single_agent::remove_all_neibor()
{
    for(int it=1;it<=neib_num;it++)
    {
        neib_map.remove(it);
    }
    neib_num=0;
}

void Single_agent::remove_all_closepoint()
{
    for(int it=1;it<=obs_closet_point_num;it++)
    {
        closepoint_map.remove(it);
    }
    obs_closet_point_num=0;
}

void Single_agent::append_closepointpair(int j, pos_xy closest)
{
    obs_closet_point_num++;
    closepoint_map.insert(j,closest);


}

