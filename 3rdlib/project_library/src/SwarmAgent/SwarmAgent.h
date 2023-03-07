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

    void appendNeibor(SwarmAgent* agent,double dis);
    void remove_all_closepoint();
    void sorting();
    void swap(int order1,int order2);
    void remove_all_neibors();
    void append_closepointpair(int j,ClosePoint* closest);
    virtual void state_update()=0; //用来填充angle,velxy,posxy的步骤，取决于statevector是如何安排的
    virtual void sensorfunction()=0;
    virtual void broadcastfunction()=0;
    virtual void controlfunction()=0;
    virtual SwarmAgent* clone_agent()=0;
    virtual Eigen::MatrixXd state_space_equation()=0;
    virtual ~SwarmAgent(){}
    int neib_num;
    int obs_closet_point_num;
    int ID;
    int status_num;
    int action_num;
    double communication_range;
    double collision_r;
    double heading_angle;
    QMap<int,SwarmAgent*> neib_map; //插入顺序和对象
    QMap<int,ClosePoint*> closepoint_map;//插入顺序和障碍物最近点
    QMap<int,double> neib_Map_distance;
    Eigen::MatrixXd pos_xy;
    Eigen::MatrixXd vel_xy;
    Eigen::MatrixXd state_vector;
    Eigen::MatrixXd act_vector;
private:


};


#endif // SWARMAGENT_H
