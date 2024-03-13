#include "ocu_car_manager_simActivator.h"


ocu_car_manager_simActivator* ocu_car_manager_simActivator::m_instance=Q_NULLPTR;
PluginContext* ocu_car_manager_simActivator::m_CONTEXT=Q_NULLPTR;
ocu_car_manager_simActivator::ocu_car_manager_simActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void ocu_car_manager_simActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void ocu_car_manager_simActivator::start()
{
    m_manager=new startwindow;
}
void ocu_car_manager_simActivator::stop()
{
delete this;

}
