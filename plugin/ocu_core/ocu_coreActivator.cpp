#include "ocu_coreActivator.h"


ocu_coreActivator* ocu_coreActivator::m_instance=Q_NULLPTR;
PluginContext* ocu_coreActivator::m_CONTEXT=Q_NULLPTR;
ocu_coreActivator::ocu_coreActivator(QObject *parent) : QObject(parent),m_manager(NULL)
{
    m_instance=this;
}
void ocu_coreActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void ocu_coreActivator::start()
{
    m_manager=new coremainwindow;
}
void ocu_coreActivator::stop()
{
delete this;

}
