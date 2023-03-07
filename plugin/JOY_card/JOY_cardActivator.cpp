#include "JOY_cardActivator.h"


JOY_cardActivator* JOY_cardActivator::m_instance=Q_NULLPTR;
PluginContext* JOY_cardActivator::m_CONTEXT=Q_NULLPTR;
JOY_cardActivator::JOY_cardActivator(QObject *parent) : QObject(parent),m_main(NULL)
{
    m_instance=this;
}
void JOY_cardActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void JOY_cardActivator::start()
{
    m_main=new main_stream;
}
void JOY_cardActivator::stop()
{
delete this;

}
