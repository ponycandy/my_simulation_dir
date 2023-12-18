#include "OpenCVGraphActivator.h"


OpenCVGraphActivator* OpenCVGraphActivator::m_instance=Q_NULLPTR;
PluginContext* OpenCVGraphActivator::m_CONTEXT=Q_NULLPTR;
OpenCVGraphActivator::OpenCVGraphActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void OpenCVGraphActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void OpenCVGraphActivator::start()
{

}
void OpenCVGraphActivator::stop()
{
delete this;

}
