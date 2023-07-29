#include "testautogradActivator.h"


testautogradActivator* testautogradActivator::m_instance=Q_NULLPTR;
PluginContext* testautogradActivator::m_CONTEXT=Q_NULLPTR;
testautogradActivator::testautogradActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void testautogradActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void testautogradActivator::start()
{
    m_main=new Testmain;
}
void testautogradActivator::stop()
{
    delete this;

}
