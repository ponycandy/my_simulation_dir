#include "Vehicle_Swarm_UWB_simulatorActivator.h"


Vehicle_Swarm_UWB_simulatorActivator* Vehicle_Swarm_UWB_simulatorActivator::m_instance=Q_NULLPTR;
PluginContext* Vehicle_Swarm_UWB_simulatorActivator::m_CONTEXT=Q_NULLPTR;
Vehicle_Swarm_UWB_simulatorActivator::Vehicle_Swarm_UWB_simulatorActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Vehicle_Swarm_UWB_simulatorActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Vehicle_Swarm_UWB_simulatorActivator::start()
{
    m_manager=new simmanager;
}
void Vehicle_Swarm_UWB_simulatorActivator::stop()
{
delete this;

}
