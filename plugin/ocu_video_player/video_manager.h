#ifndef VIDEO_MANAGER_H
#define VIDEO_MANAGER_H

#include "service/VideoCoreservice.h"
#include "video_display_widget.h"
class video_manager:public QObject,public VideoCoreservice
{
    Q_OBJECT
    Q_INTERFACES(VideoCoreservice)
public:
    video_manager(QObject *parent = nullptr);
    video_display_widget *m_display;
    QWidget * getVideoPlayerWindow() override;
    void setrtmpPath(QString streampath) override;
    void playlocalvideo(QString filename) override;
    VideoCoreservice* cloneservice() override;
    void start_streaming() override;
    void stop_streaming() override;



};

#endif // VIDEO_MANAGER_H
