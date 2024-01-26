
#ifndef VIDEOCORESERVICE_H
#define VIDEOCORESERVICE_H

#include <QObject>
class VideoCoreservice
{
public:
    virtual ~VideoCoreservice(){}
    virtual QWidget * getVideoPlayerWindow()=0;
    virtual void playlocalvideo(QString filename)=0;
    virtual VideoCoreservice* cloneservice()=0;
    virtual void setrtmpPath(QString streampath)=0;
    virtual void start_streaming()=0;
    virtual void stop_streaming()=0;
};
#define VideoCoreservice_iid "VideoCoreservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(VideoCoreservice,VideoCoreservice_iid  )
QT_END_NAMESPACE

#endif

