#include "video_manager.h"
#include "service/ocu_car_coreservice.h"
#include "ocu_video_playerActivator.h"
video_manager::video_manager(QObject *parent) : QObject(parent),m_display(nullptr)
{
    m_display=new video_display_widget;
    // ocu_car_coreservice *m_service=ocu_video_playerActivator::getService<ocu_car_coreservice>("ocu_car_coreservice");
    // m_service->addView()
}

QWidget *video_manager::getVideoPlayerWindow()
{

    return m_display;

}

void video_manager::setrtmpPath(QString streampath)
{
    //检查结尾，如果是视频格式后缀名那么
    if(streampath.count('.')==1)//视频文件
    {
        playlocalvideo(streampath);
    }
    else//推流文件
    {
        m_display->pathname=streampath;
        m_display->mode=0;
    }

}

void video_manager::playlocalvideo(QString filename)
{
    m_display->pathname=filename;
    m_display->mode=1;
}

VideoCoreservice *video_manager::cloneservice()
{
    video_manager *manager_new=new video_manager;
    return manager_new;
}

void video_manager::start_streaming()
{
  //  不允许从外部开始，只允许从内部开始
}

void video_manager::stop_streaming()
{

}
