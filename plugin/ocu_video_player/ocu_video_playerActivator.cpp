#include "ocu_video_playerActivator.h"


ocu_video_playerActivator* ocu_video_playerActivator::m_instance=Q_NULLPTR;
PluginContext* ocu_video_playerActivator::m_CONTEXT=Q_NULLPTR;
ocu_video_playerActivator::ocu_video_playerActivator(QObject *parent) : QObject(parent),m_video(NULL)
{
    m_instance=this;
}
void ocu_video_playerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void ocu_video_playerActivator::start()
{
    m_video=new video_manager;
    ocu_video_playerActivator::registerservice(m_video,"VideoCoreservice");
}
void ocu_video_playerActivator::stop()
{
delete this;

}
