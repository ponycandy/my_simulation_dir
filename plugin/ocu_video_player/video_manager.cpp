#include "video_manager.h"
#include "avplayer/avdecoder.h"
video_manager::video_manager(QObject *parent) : QObject(parent),m_display(nullptr)
{
    m_display=new video_display_widget;

}

QWidget *video_manager::getVideoPlayerWindow()
{

    return m_display;

}

void video_manager::setrtmpPath(QString streampath)
{
    m_display->pathname=streampath;
    m_display->m_pAvPlayer->m_pAvDecoder->play_flag=1;
}

void video_manager::playlocalvideo(QString filename)
{
    m_display->pathname=filename;
    m_display->m_pAvPlayer->m_pAvDecoder->play_flag=0;
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
