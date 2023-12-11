#include "simulatormanager.h"
#include "SimulatorActivator.h"
SimulatorManager::SimulatorManager(QObject *parent) : QObject(parent)
{
    delt_t=30;//ms
    m_sim=new Simer(delt_t);

}

void SimulatorManager::set_delta_t(double delta_t)
{
    delt_t=delta_t;
    m_sim->dt=delt_t;
}

void SimulatorManager::start_sim()
{
    if(step_in_mode_flag==0)
    {
        m_sim->run();
    }
    else
    {
//do nothing wait for the step in
    }
}

void SimulatorManager::set_ODE(ODE_functor *functor)
{
    m_sim->functor=functor;
}

void SimulatorManager::step_in()
{
    m_sim->stepin();
}

void SimulatorManager::set_step_in_mode(int flag)
{
    step_in_mode_flag=1;
}

void SimulatorManager::step_in_control()
{
    m_sim->functor->control(m_sim->sensor_data,m_sim->state_array);
}

void SimulatorManager::step_in_ode()
{
    m_sim->functor->ode_function(m_sim->act_array,m_sim->state_array);

}

void SimulatorManager::step_in_sensor()
{
    m_sim->functor->sensor(m_sim->state_array);

}

void SimulatorManager::step_in_broadcast()
{
    m_sim->functor->broad_cast(m_sim->state_array,m_sim->act_array,m_sim->sensor_data);
}

SimDynamicsservice *SimulatorManager::cloneservice()
{
    SimulatorManager *new_service=new SimulatorManager;
    return new_service;
}
