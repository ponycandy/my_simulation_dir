#include "test_NMPC_PluginActivator.h"


test_NMPC_PluginActivator* test_NMPC_PluginActivator::m_instance=Q_NULLPTR;
PluginContext* test_NMPC_PluginActivator::m_CONTEXT=Q_NULLPTR;
test_NMPC_PluginActivator::test_NMPC_PluginActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void test_NMPC_PluginActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void test_NMPC_PluginActivator::start()
{
    m_main=new main_exe;
}
void test_NMPC_PluginActivator::stop()
{
delete this;

}
