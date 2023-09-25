#include "swarm_NLPSimulatorActivator.h"


swarm_NLPSimulatorActivator* swarm_NLPSimulatorActivator::m_instance=Q_NULLPTR;
PluginContext* swarm_NLPSimulatorActivator::m_CONTEXT=Q_NULLPTR;
swarm_NLPSimulatorActivator::swarm_NLPSimulatorActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void swarm_NLPSimulatorActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void swarm_NLPSimulatorActivator::start()
{
    m_manager=new simmanager;
}
void swarm_NLPSimulatorActivator::stop()
{
delete this;

}
