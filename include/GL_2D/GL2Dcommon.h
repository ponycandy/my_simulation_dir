#ifndef GL2DCOMMON_H
#define GL2DCOMMON_H
#include <QPolygonF>
#include <Eigen/Core>
#include <QMap>
#include <Eigen/Dense>
#include <iostream>
#include <vector>


struct pos_xy
{

    double x;
    double y;
    double angle;
    int last_vertex;
    int next_vertex;
    int obs_ID;
    double edge1_x;
    double edge1_y;
    double edge2_x;
    double edge2_y;


};
struct prj_range
{
    double x_min;
    double x_max;
};
struct collison_result
{
    int flag;
    pos_xy closest_point;

};

struct collison_result2
{
    int flag;
    int collisionnum;
    std::vector<pos_xy> collision;

};
struct single_obstacle
{
    double x_low;
    double x_up;
    double y_low;
    double y_up;
    int ID;
    QPolygonF vertex_map;
    int vertex_num;

};
class Single_agent
{
public:
    Eigen::MatrixXd state;
     Eigen::MatrixXd vel;
       Eigen::MatrixXd pos;
    Eigen::MatrixXd act;
    QMap<int,Single_agent*> neib_map;
    QMap<int,pos_xy> closepoint_map;
    int ID;
    int neib_num;
    double angle;
    double communication_range;
    double collision_r;
    int obs_closet_point_num;
    Single_agent()
    {
        state.resize(4,1);
        state.setZero();
        vel.resize(2,1);
        vel.setZero();
        pos.resize(2,1);
        pos.setZero();
        act.resize(2,1);
        act.setZero();
        neib_num=0;obs_closet_point_num=0;
    };


    void appendNeibor(Single_agent *neib)
    {
        neib_num+=1;
        neib_map.insert(neib_num,neib);
    }
    void remove_all_neibor()
    {
        for(int it=1;it<=neib_num;it++)
        {
            neib_map.remove(it);
        }
        neib_num=0;
    }
    void remove_all_closepoint()
    {
        for(int it=1;it<=obs_closet_point_num;it++)
        {
            closepoint_map.remove(it);
        }
        obs_closet_point_num=0;
    }

    void append_closepointpair(int j,pos_xy closest)
    {
        obs_closet_point_num++;
        closepoint_map.insert(j,closest);
    }

};

#endif 

