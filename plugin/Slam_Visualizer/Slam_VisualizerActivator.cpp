#include "Slam_VisualizerActivator.h"


Slam_VisualizerActivator* Slam_VisualizerActivator::m_instance=Q_NULLPTR;
PluginContext* Slam_VisualizerActivator::m_CONTEXT=Q_NULLPTR;
Slam_VisualizerActivator::Slam_VisualizerActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Slam_VisualizerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Slam_VisualizerActivator::start()
{
    m_manager=new vomanager;
}
void Slam_VisualizerActivator::stop()
{
delete this;

}
