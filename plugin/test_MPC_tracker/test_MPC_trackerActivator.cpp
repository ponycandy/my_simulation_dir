#include "test_MPC_trackerActivator.h"


test_MPC_trackerActivator* test_MPC_trackerActivator::m_instance=Q_NULLPTR;
PluginContext* test_MPC_trackerActivator::m_CONTEXT=Q_NULLPTR;
test_MPC_trackerActivator::test_MPC_trackerActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void test_MPC_trackerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void test_MPC_trackerActivator::start()
{
    m_exe=new mainexe;
}
void test_MPC_trackerActivator::stop()
{
delete this;

}
