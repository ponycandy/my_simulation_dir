#include "test_vehicle_controllerActivator.h"


test_vehicle_controllerActivator* test_vehicle_controllerActivator::m_instance=Q_NULLPTR;
PluginContext* test_vehicle_controllerActivator::m_CONTEXT=Q_NULLPTR;
test_vehicle_controllerActivator::test_vehicle_controllerActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void test_vehicle_controllerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void test_vehicle_controllerActivator::start()
{

}
void test_vehicle_controllerActivator::stop()
{
delete this;

}
