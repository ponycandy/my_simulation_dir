#include "test_MPC_nonlinear_trackingActivator.h"


test_MPC_nonlinear_trackingActivator* test_MPC_nonlinear_trackingActivator::m_instance=Q_NULLPTR;
PluginContext* test_MPC_nonlinear_trackingActivator::m_CONTEXT=Q_NULLPTR;
test_MPC_nonlinear_trackingActivator::test_MPC_nonlinear_trackingActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void test_MPC_nonlinear_trackingActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void test_MPC_nonlinear_trackingActivator::start()
{
    m_mana=new managers;
}
void test_MPC_nonlinear_trackingActivator::stop()
{
delete this;

}
