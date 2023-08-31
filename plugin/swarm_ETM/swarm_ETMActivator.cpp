#include "swarm_ETMActivator.h"


swarm_ETMActivator* swarm_ETMActivator::m_instance=Q_NULLPTR;
PluginContext* swarm_ETMActivator::m_CONTEXT=Q_NULLPTR;
swarm_ETMActivator::swarm_ETMActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void swarm_ETMActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void swarm_ETMActivator::start()
{
    m_manager=new simmanager;
}
void swarm_ETMActivator::stop()
{
delete this;

}
