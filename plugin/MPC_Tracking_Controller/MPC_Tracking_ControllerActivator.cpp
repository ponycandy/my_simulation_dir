#include "MPC_Tracking_ControllerActivator.h"


MPC_Tracking_ControllerActivator* MPC_Tracking_ControllerActivator::m_instance=Q_NULLPTR;
PluginContext* MPC_Tracking_ControllerActivator::m_CONTEXT=Q_NULLPTR;
MPC_Tracking_ControllerActivator::MPC_Tracking_ControllerActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void MPC_Tracking_ControllerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void MPC_Tracking_ControllerActivator::start()
{
    m_manager=new MPC_manager;
}
void MPC_Tracking_ControllerActivator::stop()
{
delete this;

}
