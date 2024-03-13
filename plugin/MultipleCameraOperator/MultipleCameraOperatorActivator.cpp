#include "MultipleCameraOperatorActivator.h"


MultipleCameraOperatorActivator* MultipleCameraOperatorActivator::m_instance=Q_NULLPTR;
PluginContext* MultipleCameraOperatorActivator::m_CONTEXT=Q_NULLPTR;
MultipleCameraOperatorActivator::MultipleCameraOperatorActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void MultipleCameraOperatorActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void MultipleCameraOperatorActivator::start()
{
    m_manager=new CameraManager;
}
void MultipleCameraOperatorActivator::stop()
{
delete this;

}
