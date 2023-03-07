#include "SwarmSimulatorActivator.h"


SwarmSimulatorActivator* SwarmSimulatorActivator::m_instance=Q_NULLPTR;
PluginContext* SwarmSimulatorActivator::m_CONTEXT=Q_NULLPTR;
SwarmSimulatorActivator::SwarmSimulatorActivator(QObject *parent) : QObject(parent),manager(NULL)
{
    m_instance=this;
}
void SwarmSimulatorActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void SwarmSimulatorActivator::start()
{
    manager=new simulator_manager;
    SwarmSimulatorActivator::registerservice(manager,"SwarmSimservice");
}
void SwarmSimulatorActivator::stop()
{
delete this;

}
