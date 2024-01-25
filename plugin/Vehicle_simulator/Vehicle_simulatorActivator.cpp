#include "Vehicle_simulatorActivator.h"


Vehicle_simulatorActivator* Vehicle_simulatorActivator::m_instance=Q_NULLPTR;
PluginContext* Vehicle_simulatorActivator::m_CONTEXT=Q_NULLPTR;
Vehicle_simulatorActivator::Vehicle_simulatorActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Vehicle_simulatorActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Vehicle_simulatorActivator::start()
{
    m_manager=new vehicle_manager;
}
void Vehicle_simulatorActivator::stop()
{
delete this;

}
