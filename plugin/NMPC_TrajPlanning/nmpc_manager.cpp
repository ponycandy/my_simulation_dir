#include "nmpc_manager.h"
#include <service/NMPCservice.h>
#include <NMPC_TrajPlanningActivator.h>
NMPC_manager::NMPC_manager(QObject *parent) : QObject(parent)
{

    m_nmpc_construct=new NMPC_Constructor;
    NMPC_TrajPlanningActivator::registerservice(m_nmpc_construct,"NMPCservice");
    //最后的结果存储在m_nmpc的actMat和stateMat里面
}
