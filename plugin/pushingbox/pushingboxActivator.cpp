#include "pushingboxActivator.h"


pushingboxActivator* pushingboxActivator::m_instance=Q_NULLPTR;
PluginContext* pushingboxActivator::m_CONTEXT=Q_NULLPTR;
pushingboxActivator::pushingboxActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void pushingboxActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void pushingboxActivator::start()
{
    m_manage=new simmanager;
}
void pushingboxActivator::stop()
{
delete this;

}
