#include "topicsubscriberActivator.h"


topicsubscriberActivator* topicsubscriberActivator::m_instance=Q_NULLPTR;
PluginContext* topicsubscriberActivator::m_CONTEXT=Q_NULLPTR;
topicsubscriberActivator::topicsubscriberActivator(QObject *parent) : QObject(parent),m_manager(NULL)
{
    m_instance=this;
}
void topicsubscriberActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void topicsubscriberActivator::start()
{
    m_manager=new nodemanager;
}
void topicsubscriberActivator::stop()
{
delete this;

}
