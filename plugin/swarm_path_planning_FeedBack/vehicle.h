#ifndef VEHICLE_H
#define VEHICLE_H

#include "SwarmAgent.h"
#include "QObject"
#include "service/Datalogservice.h"
#include "nonlinearplanner.h"
class vehicle:public QObject,public SwarmAgent
{
    Q_OBJECT
public:
    vehicle();
    void state_update() override; //用来填充angle,velxy,posxy的步骤，取决于statevector是如何安排的
    void sensorfunction() override;
    void setsendsig(int order);
    void trackref();
    int timenow;
    void broadcastfunction() override;
    void controlfunction() override;
    bool stable_judgement() ;
    void predicitTraj(Eigen::MatrixXd &target);
    void Getcontrol();
    void Getlookaheadpoint();
    void fault_set(int option) override;
    QMap<int , double>  nearbyagentdistance;

    SwarmAgent* clone_agent() override;
    Eigen::MatrixXd state_space_equation() override;

    int agentnum;

    int predictedN;
    int internalcount=0;

    Eigen::MatrixXd Trackref;
    Datalogservice *logger;
    NonlinearPlanner *m_planner;
    int TriggerTimecounter;
    int sigma_step;
    Eigen::MatrixXd InternalState;
    double maxmumstep;

signals:
    void LeaderBroadcast(Eigen::MatrixXd PlannedTraj);
    void Predictbroadcast(Eigen::MatrixXd targetpredict);
public slots:
    void Recievesig(Eigen::MatrixXd PlannedTraj);


};

#endif // VEHICLE_H
