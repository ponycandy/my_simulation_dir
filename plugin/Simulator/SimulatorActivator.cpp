#include "SimulatorActivator.h"


SimulatorActivator* SimulatorActivator::m_instance=Q_NULLPTR;
PluginContext* SimulatorActivator::m_CONTEXT=Q_NULLPTR;
SimulatorActivator::SimulatorActivator(QObject *parent) : QObject(parent),m_sim(NULL)
{
    m_instance=this;
}
void SimulatorActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void SimulatorActivator::start()
{
    m_sim=new SimulatorManager;
    SimulatorActivator::registerservice(m_sim,"SimDynamicsservice");
}
void SimulatorActivator::stop()
{
delete this;

}
