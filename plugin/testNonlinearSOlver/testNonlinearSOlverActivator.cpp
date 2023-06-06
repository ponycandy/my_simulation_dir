#include "testNonlinearSOlverActivator.h"


testNonlinearSOlverActivator* testNonlinearSOlverActivator::m_instance=Q_NULLPTR;
PluginContext* testNonlinearSOlverActivator::m_CONTEXT=Q_NULLPTR;
testNonlinearSOlverActivator::testNonlinearSOlverActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void testNonlinearSOlverActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void testNonlinearSOlverActivator::start()
{
    m_main=new main_exe;
}
void testNonlinearSOlverActivator::stop()
{
delete this;

}
