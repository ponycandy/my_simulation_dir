#include "SwarmSimulator_201Activator.h"


SwarmSimulator_201Activator* SwarmSimulator_201Activator::m_instance=Q_NULLPTR;
PluginContext* SwarmSimulator_201Activator::m_CONTEXT=Q_NULLPTR;
SwarmSimulator_201Activator::SwarmSimulator_201Activator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void SwarmSimulator_201Activator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void SwarmSimulator_201Activator::start()
{
    m_manager=new simulator_manager;
    SwarmSimulator_201Activator::registerservice(m_manager,"SwarmSimservice");

}
void SwarmSimulator_201Activator::stop()
{
delete this;

}
