#include "test_MPCActivator.h"


test_MPCActivator* test_MPCActivator::m_instance=Q_NULLPTR;
PluginContext* test_MPCActivator::m_CONTEXT=Q_NULLPTR;
test_MPCActivator::test_MPCActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void test_MPCActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void test_MPCActivator::start()
{

}
void test_MPCActivator::stop()
{
delete this;

}
