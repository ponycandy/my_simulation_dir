#include "testmultitopicsubscribeActivator.h"


testmultitopicsubscribeActivator* testmultitopicsubscribeActivator::m_instance=Q_NULLPTR;
PluginContext* testmultitopicsubscribeActivator::m_CONTEXT=Q_NULLPTR;
testmultitopicsubscribeActivator::testmultitopicsubscribeActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void testmultitopicsubscribeActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void testmultitopicsubscribeActivator::start()
{
    m_manager=new mqttmanager;
}
void testmultitopicsubscribeActivator::stop()
{
delete this;

}
