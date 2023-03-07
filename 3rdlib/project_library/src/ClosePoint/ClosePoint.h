#ifndef CLOSEPOINT_H
#define CLOSEPOINT_H
#include "CLOSEPOINT_global.h"
#include "Eigen/Core"
class CLOSEPOINT_EXPORT ClosePoint
{
public:
	ClosePoint();
    void update_state();

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
    Eigen::MatrixXd edg1;
    Eigen::MatrixXd edg2;
    Eigen::MatrixXd pos;

//数据含义:包含1.最近点所在的障碍物ID编号
//            2.最近点所在的边（或者顶点）的相邻两个顶点的编号
//            3.最近点与两个相邻点的连接矢量,last对应edg1
//        4.最近点的坐标
//        5.上述数据的向量化形式
    //    void calc_vetor()
    //    {
    //        pos.resize(2,1);
    //        pos(0,0)=x;
    //        pos(1,0)=y;
    //    }
private:
};


#endif // CLOSEPOINT_H
