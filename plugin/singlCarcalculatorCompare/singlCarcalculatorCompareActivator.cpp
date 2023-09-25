#include "singlCarcalculatorCompareActivator.h"


singlCarcalculatorCompareActivator* singlCarcalculatorCompareActivator::m_instance=Q_NULLPTR;
PluginContext* singlCarcalculatorCompareActivator::m_CONTEXT=Q_NULLPTR;
singlCarcalculatorCompareActivator::singlCarcalculatorCompareActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void singlCarcalculatorCompareActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void singlCarcalculatorCompareActivator::start()
{
    m_manager=new Solvermanager;

}
void singlCarcalculatorCompareActivator::stop()
{
delete this;

}
