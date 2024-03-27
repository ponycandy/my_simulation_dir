
#ifndef SIMDYNAMICSSERVICE_H
#define SIMDYNAMICSSERVICE_H

#include <QObject>
#include <include/GL_2D/ODE_functor.h>
class SimDynamicsservice
{
public:
    virtual ~SimDynamicsservice(){}
    virtual void set_delta_t(double delta_t)=0;
    virtual void start_sim()=0;
    virtual void stop_sim()=0;
    virtual void set_ODE(ODE_functor *functor)=0;
    virtual void step_in()=0;
    virtual void step_in_control()=0;
    virtual void step_in_ode()=0;
    virtual void step_in_sensor()=0;

    virtual void step_in_broadcast()=0;

    virtual void set_step_in_mode(int flag)=0;
    virtual SimDynamicsservice* cloneservice()=0;

};
#define SimDynamicsservice_iid "SimDynamicsservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(SimDynamicsservice,SimDynamicsservice_iid  )
QT_END_NAMESPACE

#endif

