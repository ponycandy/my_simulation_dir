#include "swarm_path_planning_FeedBackActivator.h"


swarm_path_planning_FeedBackActivator* swarm_path_planning_FeedBackActivator::m_instance=Q_NULLPTR;
PluginContext* swarm_path_planning_FeedBackActivator::m_CONTEXT=Q_NULLPTR;
swarm_path_planning_FeedBackActivator::swarm_path_planning_FeedBackActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void swarm_path_planning_FeedBackActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void swarm_path_planning_FeedBackActivator::start()
{
    m_manager=new simmanager;
}
void swarm_path_planning_FeedBackActivator::stop()
{
delete this;

}
