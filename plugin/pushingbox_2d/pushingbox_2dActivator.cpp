#include "pushingbox_2dActivator.h"


pushingbox_2dActivator* pushingbox_2dActivator::m_instance=Q_NULLPTR;
PluginContext* pushingbox_2dActivator::m_CONTEXT=Q_NULLPTR;
pushingbox_2dActivator::pushingbox_2dActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void pushingbox_2dActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void pushingbox_2dActivator::start()
{
    m_manager=new simmanager;
}
void pushingbox_2dActivator::stop()
{
delete this;

}
