#include "test_bit201_communication_pluginActivator.h"


test_bit201_communication_pluginActivator* test_bit201_communication_pluginActivator::m_instance=Q_NULLPTR;
PluginContext* test_bit201_communication_pluginActivator::m_CONTEXT=Q_NULLPTR;
test_bit201_communication_pluginActivator::test_bit201_communication_pluginActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void test_bit201_communication_pluginActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void test_bit201_communication_pluginActivator::start()
{
m_exec=new main_executer;
}
void test_bit201_communication_pluginActivator::stop()
{
delete this;

}
