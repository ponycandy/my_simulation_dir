#include "testffmpegutilityActivator.h"


testffmpegutilityActivator* testffmpegutilityActivator::m_instance=Q_NULLPTR;
PluginContext* testffmpegutilityActivator::m_CONTEXT=Q_NULLPTR;
testffmpegutilityActivator::testffmpegutilityActivator(QObject *parent) : QObject(parent),m_form(NULL)
{
    m_instance=this;
}
void testffmpegutilityActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void testffmpegutilityActivator::start()
{
    m_form=new Form;
}
void testffmpegutilityActivator::stop()
{
delete this;

}
