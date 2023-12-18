#include "Test_using_gpcsActivator.h"


Test_using_gpcsActivator* Test_using_gpcsActivator::m_instance=Q_NULLPTR;
PluginContext* Test_using_gpcsActivator::m_CONTEXT=Q_NULLPTR;
Test_using_gpcsActivator::Test_using_gpcsActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Test_using_gpcsActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Test_using_gpcsActivator::start()
{
    exec=new mainExecution;
}
void Test_using_gpcsActivator::stop()
{
delete this;

}
