#ifndef VEHICLE_H
#define VEHICLE_H

#include "SwarmAgent.h"
#include "hmagent.h"
#include "service/SimDynamicsservice.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"


class vehicle:public SwarmAgent
{
public:
    vehicle();
    void state_update() override; //用来填充angle,velxy,posxy的步骤，取决于statevector是如何安排的
    void sensorfunction() override;
    double normalize(double angle) ;
    void broadcastfunction() override;
    void controlfunction() override;
    bool stable_judgement() ;
    void predicitTraj();
    void Getcontrol();
    void Getlookaheadpoint();
    void fault_set(int option) override;
    SwarmAgent* clone_agent() override;
    Eigen::MatrixXd state_space_equation() override;
    Eigen::MatrixXd refpos;
    HMagent *singleone;
    double maxspeed;
    double maxOmega;
    int agentnum;
    int falseflag=0;
    int predicthorizon=0;
    int controlhorizon=0;
    QMap<int, SwarmAgent *> agentgroup;
    SimDynamicsservice *dysim;
    std::shared_ptr<spdlog::logger> my_logger;

};

#endif // VEHICLE_H
