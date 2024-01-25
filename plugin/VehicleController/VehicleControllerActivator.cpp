#include "VehicleControllerActivator.h"


VehicleControllerActivator* VehicleControllerActivator::m_instance=Q_NULLPTR;
PluginContext* VehicleControllerActivator::m_CONTEXT=Q_NULLPTR;
VehicleControllerActivator::VehicleControllerActivator(QObject *parent) : QObject(parent),m_manager(NULL)
{
    m_instance=this;
}
void VehicleControllerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void VehicleControllerActivator::start()
{
    m_manager=new VehicleManager;
}
void VehicleControllerActivator::stop()
{
delete this;

}
