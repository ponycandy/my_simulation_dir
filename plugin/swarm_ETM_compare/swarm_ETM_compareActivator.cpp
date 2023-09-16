#include "swarm_ETM_compareActivator.h"


swarm_ETM_compareActivator* swarm_ETM_compareActivator::m_instance=Q_NULLPTR;
PluginContext* swarm_ETM_compareActivator::m_CONTEXT=Q_NULLPTR;
swarm_ETM_compareActivator::swarm_ETM_compareActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void swarm_ETM_compareActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void swarm_ETM_compareActivator::start()
{
    m_manager=new simmanager;
}
void swarm_ETM_compareActivator::stop()
{
delete this;

}
