#param once

#include <QPolygonF>
#include <Eigen/Core>
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
//    Eigen::MatrixXd edg1;
//    Eigen::MatrixXd edg2;
//    Eigen::MatrixXd pos;
//    pos_xy()
//    {
//        edg1.resize(2,1);edg1.setZero();
//        edg2.resize(2,1);edg2.setZero();

//        pos.resize(2,1);pos.setZero();

//    }
//    void calc_vetor()
//    {
//        pos.resize(2,1);
//        pos(0,0)=x;
//        pos(1,0)=y;
//    }


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

