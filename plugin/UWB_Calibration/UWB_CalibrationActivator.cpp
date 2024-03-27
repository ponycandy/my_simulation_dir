#include "UWB_CalibrationActivator.h"


UWB_CalibrationActivator* UWB_CalibrationActivator::m_instance=Q_NULLPTR;
PluginContext* UWB_CalibrationActivator::m_CONTEXT=Q_NULLPTR;
UWB_CalibrationActivator::UWB_CalibrationActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void UWB_CalibrationActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void UWB_CalibrationActivator::start()
{

}
void UWB_CalibrationActivator::stop()
{
delete this;

}
