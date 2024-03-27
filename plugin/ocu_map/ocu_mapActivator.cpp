#include "ocu_mapActivator.h"
#include "include/OSGIEVENT.h"

ocu_mapActivator* ocu_mapActivator::m_instance=Q_NULLPTR;
PluginContext* ocu_mapActivator::m_CONTEXT=Q_NULLPTR;
ocu_mapActivator::ocu_mapActivator(QObject *parent) : QObject(parent),m_manager(NULL)
{
    m_instance=this;
}
void ocu_mapActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void ocu_mapActivator::start()
{
    m_manager=new MapManager;
    ocu_mapActivator::registerservice(m_manager,"MapService");
    ocu_mapActivator::subscribeslot(m_manager,SLOT(slot_start_record_points()),OSGIEVENT::SIG_MAP_SELECT_POINTS,Qt::QueuedConnection);
    ocu_mapActivator::subscribeslot(m_manager,SLOT(slot_stop_record_points()),OSGIEVENT::SIG_MAP_STOP_SELECT_POINTS,Qt::QueuedConnection);
    ocu_mapActivator::subscribeslot(m_manager,SLOT(slot_Autonavi_points()),OSGIEVENT::SIG_MAP_AUTONAVIGATE_POINTS,Qt::QueuedConnection);

}
void ocu_mapActivator::stop()
{
delete this;

}
