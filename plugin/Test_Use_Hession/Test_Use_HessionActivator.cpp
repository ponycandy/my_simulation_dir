#include "Test_Use_HessionActivator.h"


Test_Use_HessionActivator* Test_Use_HessionActivator::m_instance=Q_NULLPTR;
PluginContext* Test_Use_HessionActivator::m_CONTEXT=Q_NULLPTR;
Test_Use_HessionActivator::Test_Use_HessionActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Test_Use_HessionActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Test_Use_HessionActivator::start()
{

}
void Test_Use_HessionActivator::stop()
{
delete this;

}
