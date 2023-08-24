#ifndef VEHICLE_H
#define VEHICLE_H

#include "SwarmAgent.h"
class vehicle:public SwarmAgent
{
public:
    vehicle();
    void state_update() override; //用来填充angle,velxy,posxy的步骤，取决于statevector是如何安排的
    void sensorfunction() override;
    void broadcastfunction() override;
    void controlfunction() override;
    void fault_set(int option) override;
    double get_angle(double vx, double vy);
    SwarmAgent* clone_agent() override;
    Eigen::MatrixXd state_space_equation() override;
    Eigen::MatrixXd refpos;
    int falseflag=0;
};

#endif // VEHICLE_H
