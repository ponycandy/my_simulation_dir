#include "swarm_rl_experimentActivator.h"


swarm_rl_experimentActivator* swarm_rl_experimentActivator::m_instance=Q_NULLPTR;
PluginContext* swarm_rl_experimentActivator::m_CONTEXT=Q_NULLPTR;
swarm_rl_experimentActivator::swarm_rl_experimentActivator(QObject *parent) : QObject(parent),m_main(NULL)
{
    m_instance=this;
}
void swarm_rl_experimentActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void swarm_rl_experimentActivator::start()
{
    m_main=new main_stream;
}
void swarm_rl_experimentActivator::stop()
{
delete this;

}
