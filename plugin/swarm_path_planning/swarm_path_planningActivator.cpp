#include "swarm_path_planningActivator.h"


swarm_path_planningActivator* swarm_path_planningActivator::m_instance=Q_NULLPTR;
PluginContext* swarm_path_planningActivator::m_CONTEXT=Q_NULLPTR;
swarm_path_planningActivator::swarm_path_planningActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void swarm_path_planningActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void swarm_path_planningActivator::start()
{
    m_manager=new planner_manager;
}
void swarm_path_planningActivator::stop()
{
delete this;

}
