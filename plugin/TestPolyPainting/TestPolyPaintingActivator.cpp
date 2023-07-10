#include "TestPolyPaintingActivator.h"

TestPolyPaintingActivator* TestPolyPaintingActivator::m_instance=Q_NULLPTR;
PluginContext* TestPolyPaintingActivator::m_CONTEXT=Q_NULLPTR;
TestPolyPaintingActivator::TestPolyPaintingActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void TestPolyPaintingActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void TestPolyPaintingActivator::start()
{
    m_g=new graphing;
}
void TestPolyPaintingActivator::stop()
{
delete this;

}
