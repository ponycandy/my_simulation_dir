#ifndef VEHICLE_H
#define VEHICLE_H

#include "SwarmAgent.h"
#include "service/SimDynamicsservice.h"
#include "service/CollisionDetectservice.h"
#include "service/Datalogservice.h"
#include "QObject"
#include <SwarmObstacle.h>
class vehicle:public QObject,public SwarmAgent
{
    Q_OBJECT
public:
    vehicle();
    void state_update() override; //用来填充angle,velxy,posxy的步骤，取决于statevector是如何安排的
    void sensorfunction() override;
    Eigen::MatrixXd predict_Collistion(ClosePoint * clagent);
    void broadcastfunction() override;
    void controlfunction() override;
    bool stable_judgement() ;
    void predicitTraj();
    void Getcontrol();
    void Getlookaheadpoint();
    void fault_set(int option) override;
    void setsendsig(int order);
    SwarmAgent* clone_agent() override;
    Eigen::MatrixXd state_space_equation() override;
    Eigen::MatrixXd refpos;
    Eigen::MatrixXd m_e_T;
    Eigen::MatrixXd m_v_T;
    Eigen::MatrixXd m_v_n;
    Eigen::MatrixXd leader_act_temp;
    Eigen::MatrixXd leader_pos_temp;
    Eigen::MatrixXd leader_vel_temp;
    CollisionDetectservice *m_service;
    QMap<int , double>  nearbyagentdistance;
    double maxspeed;
    double maxOmega;
    int agentnum;
    int falseflag=0;
    int predicthorizon=0;
    int controlhorizon=0;
    Datalogservice *M_logger;
    QMap<int,SwarmObstacle*> obsbounding_group;
    int steps=0;
signals:
    void updatetarget(double x,double y,double phi);
    void updateleader(double x,double y,double phi);
    void LeaderBroadcast(Eigen::MatrixXd e_T,Eigen::MatrixXd v_T,Eigen::MatrixXd v_n,Eigen::MatrixXd othersignal);
public slots:
    void Broadcastupdate(Eigen::MatrixXd e_t,Eigen::MatrixXd v_t,Eigen::MatrixXd v_n,Eigen::MatrixXd othersignal);
};

#endif // VEHICLE_H
