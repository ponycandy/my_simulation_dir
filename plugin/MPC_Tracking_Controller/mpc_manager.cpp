
#include "mpc_manager.h"
#include <service/MPC_Trackerservice.h>
#include <MPC_Tracking_ControllerActivator.h>


MPC_manager::MPC_manager(QObject *parent) : QObject(parent)
{
    m_mpc_construct=new MPC_Constructor;
    MPC_Tracking_ControllerActivator::registerservice(m_mpc_construct,"MPC_Trackerservice");
    //最后的结果存储在m_nmpc的actMat和stateMat里面
}
