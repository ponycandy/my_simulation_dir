#ifndef SWARMAGENT_H
#define SWARMAGENT_H
#include "SWARMAGENT_global.h"
#include "QMap"
#include <Eigen/Core>
#include <ClosePoint.h>
class SWARMAGENT_EXPORT SwarmAgent
{
public:
    SwarmAgent();
    void appendNeibor(SwarmAgent* agent);
    void remove_all_closepoint();
    void append_closepointpair(int j,ClosePoint* closest);
    int neib_num;
    int obs_closet_point_num;
    int ID;
    double communication_range;
    double collision_r;
    double heading_angle;
    QMap<int,SwarmAgent*> neib_map; //插入顺序和对象
    QMap<int,ClosePoint*> closepoint_map;//插入顺序和障碍物最近点
    Eigen::MatrixXd pos_xy;
    Eigen::MatrixXd vel_xy;
    Eigen::MatrixXd state_vector;
    Eigen::MatrixXd act_vector;
private:


};


#endif // SWARMAGENT_H
