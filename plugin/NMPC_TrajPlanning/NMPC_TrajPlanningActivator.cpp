#include "NMPC_TrajPlanningActivator.h"


NMPC_TrajPlanningActivator* NMPC_TrajPlanningActivator::m_instance=Q_NULLPTR;
PluginContext* NMPC_TrajPlanningActivator::m_CONTEXT=Q_NULLPTR;
NMPC_TrajPlanningActivator::NMPC_TrajPlanningActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void NMPC_TrajPlanningActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void NMPC_TrajPlanningActivator::start()
{
    m_manager=new NMPC_manager;
}
void NMPC_TrajPlanningActivator::stop()
{
delete this;

}
