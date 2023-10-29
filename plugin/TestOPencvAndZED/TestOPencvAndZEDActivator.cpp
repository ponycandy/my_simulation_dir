#include "TestOPencvAndZEDActivator.h"


TestOPencvAndZEDActivator* TestOPencvAndZEDActivator::m_instance=Q_NULLPTR;
PluginContext* TestOPencvAndZEDActivator::m_CONTEXT=Q_NULLPTR;
TestOPencvAndZEDActivator::TestOPencvAndZEDActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void TestOPencvAndZEDActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void TestOPencvAndZEDActivator::start()
{
    m_viewer=new ZEDviewer;
}
void TestOPencvAndZEDActivator::stop()
{
    delete this;

}
