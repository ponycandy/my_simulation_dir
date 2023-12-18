#include "swarm_NMPC_trajectory_plannerActivator.h"


swarm_NMPC_trajectory_plannerActivator* swarm_NMPC_trajectory_plannerActivator::m_instance=Q_NULLPTR;
PluginContext* swarm_NMPC_trajectory_plannerActivator::m_CONTEXT=Q_NULLPTR;
swarm_NMPC_trajectory_plannerActivator::swarm_NMPC_trajectory_plannerActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void swarm_NMPC_trajectory_plannerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void swarm_NMPC_trajectory_plannerActivator::start()
{

}
void swarm_NMPC_trajectory_plannerActivator::stop()
{
delete this;

}
