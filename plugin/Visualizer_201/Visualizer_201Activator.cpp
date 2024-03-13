#include "Visualizer_201Activator.h"


Visualizer_201Activator* Visualizer_201Activator::m_instance=Q_NULLPTR;
PluginContext* Visualizer_201Activator::m_CONTEXT=Q_NULLPTR;
Visualizer_201Activator::Visualizer_201Activator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Visualizer_201Activator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Visualizer_201Activator::start()
{
    m_anim=new animator_manager;
}
void Visualizer_201Activator::stop()
{
delete this;

}
