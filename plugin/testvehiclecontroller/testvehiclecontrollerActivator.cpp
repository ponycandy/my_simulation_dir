#include "testvehiclecontrollerActivator.h"


testvehiclecontrollerActivator* testvehiclecontrollerActivator::m_instance=Q_NULLPTR;
PluginContext* testvehiclecontrollerActivator::m_CONTEXT=Q_NULLPTR;
testvehiclecontrollerActivator::testvehiclecontrollerActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void testvehiclecontrollerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void testvehiclecontrollerActivator::start()
{
    m_manager=new messagemanager;
}
void testvehiclecontrollerActivator::stop()
{
delete this;

}
