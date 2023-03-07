#ifndef VEHICLE_H
#define VEHICLE_H

#include "SwarmAgent.h"
class vehicle:public SwarmAgent
{
public:
    vehicle();
    double get_angle(double vx,double vy);
    void state_update() override; //用来填充angle,velxy,posxy的步骤，取决于statevector是如何安排的
    void sensorfunction() override;
    void broadcastfunction() override;
    void controlfunction() override;
    SwarmAgent* clone_agent() override;
    Eigen::MatrixXd state_space_equation() override;
};

#endif // VEHICLE_H
