#include "singleCarCalculatorActivator.h"


singleCarCalculatorActivator* singleCarCalculatorActivator::m_instance=Q_NULLPTR;
PluginContext* singleCarCalculatorActivator::m_CONTEXT=Q_NULLPTR;
singleCarCalculatorActivator::singleCarCalculatorActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void singleCarCalculatorActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void singleCarCalculatorActivator::start()
{
    m_manager=new Solvermanager;
}
void singleCarCalculatorActivator::stop()
{
delete this;

}
