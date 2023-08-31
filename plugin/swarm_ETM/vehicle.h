#ifndef VEHICLE_H
#define VEHICLE_H

#include "SwarmAgent.h"
#include "QObject"
//#include "grayaray.h"

class vehicle:public QObject,public SwarmAgent
{
    Q_OBJECT
public:
    vehicle();
    void state_update() override; //用来填充angle,velxy,posxy的步骤，取决于statevector是如何安排的
    void sensorfunction() override;
    void setsendsig(int order);


    void broadcastfunction() override;
    void controlfunction() override;
    bool stable_judgement() ;
    void predicitTraj();
    void Getcontrol();
    void Getlookaheadpoint();
    void fault_set(int option) override;
    QMap<int , double>  nearbyagentdistance;
    SwarmAgent* clone_agent() override;
    Eigen::MatrixXd state_space_equation() override;
    Eigen::MatrixXd refpos;
    Eigen::MatrixXd lastpos_xy;
    int agentnum;
    int cacheOBSclpnum;
    double cacheSigma;
    double sigma;
    int predictedN;
    Eigen::MatrixXd m_e_T;
    Eigen::MatrixXd m_v_T;
    Eigen::MatrixXd m_v_n;
    Eigen::MatrixXd leader_act_temp;
    Eigen::MatrixXd leader_pos_temp;
    Eigen::MatrixXd leader_vel_temp;
//    GrayAray *predictguy;
signals:
    void updatetarget(double x,double y,double phi);
    void LeaderBroadcast(Eigen::MatrixXd e_T,Eigen::MatrixXd v_T,Eigen::MatrixXd v_n,Eigen::MatrixXd othersignal);
public slots:
    void Broadcastupdate(Eigen::MatrixXd e_t,Eigen::MatrixXd v_t,Eigen::MatrixXd v_n,Eigen::MatrixXd othersignal);


};

#endif // VEHICLE_H
