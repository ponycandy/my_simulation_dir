#ifndef HMAGENT_H
#define HMAGENT_H

#include <QObject>
#include "SwarmAgent.h"
class HMagent : public QObject,public SwarmAgent
{
    Q_OBJECT
public:
    explicit HMagent(QObject *parent = nullptr);
    void state_update() override;
    void sensorfunction() override;
    void broadcastfunction() override;
    void controlfunction() override;
    void fault_set(int option) override;
    double get_angle(double vx, double vy);
    SwarmAgent* clone_agent() override;
    Eigen::MatrixXd state_space_equation() override;
    Eigen::MatrixXd target_state;

signals:

};

#endif // HMAGENT_H
