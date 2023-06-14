#include "Swarm_NMPC_PlannerActivator.h"


Swarm_NMPC_PlannerActivator* Swarm_NMPC_PlannerActivator::m_instance=Q_NULLPTR;
PluginContext* Swarm_NMPC_PlannerActivator::m_CONTEXT=Q_NULLPTR;
Swarm_NMPC_PlannerActivator::Swarm_NMPC_PlannerActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Swarm_NMPC_PlannerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Swarm_NMPC_PlannerActivator::start()
{
    m_manager=new solver_manager;
}
void Swarm_NMPC_PlannerActivator::stop()
{
    delete this;

}
