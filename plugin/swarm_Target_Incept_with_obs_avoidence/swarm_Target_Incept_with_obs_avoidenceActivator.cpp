#include "swarm_Target_Incept_with_obs_avoidenceActivator.h"


swarm_Target_Incept_with_obs_avoidenceActivator* swarm_Target_Incept_with_obs_avoidenceActivator::m_instance=Q_NULLPTR;
PluginContext* swarm_Target_Incept_with_obs_avoidenceActivator::m_CONTEXT=Q_NULLPTR;
swarm_Target_Incept_with_obs_avoidenceActivator::swarm_Target_Incept_with_obs_avoidenceActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void swarm_Target_Incept_with_obs_avoidenceActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void swarm_Target_Incept_with_obs_avoidenceActivator::start()
{
    m_manager=new simmanager;
}
void swarm_Target_Incept_with_obs_avoidenceActivator::stop()
{
delete this;

}
