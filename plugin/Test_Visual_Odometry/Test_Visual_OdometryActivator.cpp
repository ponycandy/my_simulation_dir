#include "Test_Visual_OdometryActivator.h"


Test_Visual_OdometryActivator* Test_Visual_OdometryActivator::m_instance=Q_NULLPTR;
PluginContext* Test_Visual_OdometryActivator::m_CONTEXT=Q_NULLPTR;
Test_Visual_OdometryActivator::Test_Visual_OdometryActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Test_Visual_OdometryActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Test_Visual_OdometryActivator::start()
{

}
void Test_Visual_OdometryActivator::stop()
{
delete this;

}
