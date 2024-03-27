#ifndef SIMULATORMANAGER_H
#define SIMULATORMANAGER_H

#include <QObject>
#include <service/SimDynamicsservice.h>
#include <simer.h>
class SimulatorManager : public QObject,public SimDynamicsservice
{
    Q_OBJECT
    Q_INTERFACES(SimDynamicsservice)
public:
    explicit SimulatorManager(QObject *parent = nullptr);
    void set_delta_t(double delta_t) override;
    void start_sim() override;
    void stop_sim() override;
    void set_ODE(ODE_functor *functor) override;
    void step_in() override;
    void set_step_in_mode(int flag) override;
    void step_in_control() override;
    void step_in_ode() override;
    void step_in_sensor() override;

    void step_in_broadcast() override;
    SimDynamicsservice* cloneservice() override;

    double delt_t;
    int step_in_mode_flag=0;
    Simer *m_sim;

signals:

};

#endif // SIMULATORMANAGER_H
