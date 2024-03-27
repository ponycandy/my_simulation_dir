#include "Vehicle_swarm_controllerActivator.h"


Vehicle_swarm_controllerActivator* Vehicle_swarm_controllerActivator::m_instance=Q_NULLPTR;
PluginContext* Vehicle_swarm_controllerActivator::m_CONTEXT=Q_NULLPTR;
Vehicle_swarm_controllerActivator::Vehicle_swarm_controllerActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Vehicle_swarm_controllerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Vehicle_swarm_controllerActivator::start()
{
    m_manager=new Device_manager;
}
void Vehicle_swarm_controllerActivator::stop()
{
delete this;

}
