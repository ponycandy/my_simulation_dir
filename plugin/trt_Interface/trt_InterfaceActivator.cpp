#include "trt_InterfaceActivator.h"


trt_InterfaceActivator* trt_InterfaceActivator::m_instance=Q_NULLPTR;
PluginContext* trt_InterfaceActivator::m_CONTEXT=Q_NULLPTR;
trt_InterfaceActivator::trt_InterfaceActivator(QObject *parent) : QObject(parent),m_manager(NULL)
{
    m_instance=this;
}
void trt_InterfaceActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void trt_InterfaceActivator::start()
{
    m_manager=new trtmanager;
}
void trt_InterfaceActivator::stop()
{
delete this;

}
