#include "Swarm_obstacle_avoidActivator.h"


Swarm_obstacle_avoidActivator* Swarm_obstacle_avoidActivator::m_instance=Q_NULLPTR;
PluginContext* Swarm_obstacle_avoidActivator::m_CONTEXT=Q_NULLPTR;
Swarm_obstacle_avoidActivator::Swarm_obstacle_avoidActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Swarm_obstacle_avoidActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Swarm_obstacle_avoidActivator::start()
{
    m_manager=new simmanager;
}
void Swarm_obstacle_avoidActivator::stop()
{
delete this;

}
