#ifndef PUB_THREAD_H
#define PUB_THREAD_H

#include <QObject>
#include <xtlevent.h>

#include <service/Datamanageservice.h>
#include <service/eventservice.h>

#ifdef __linux__
#include <ros/ros.h>
#endif

class pub_thread : public QObject,public EventService
{
    Q_OBJECT
public:
    explicit pub_thread(QObject *parent = nullptr);

    Datamanageservice *servicehandle;
    int on_pub=0;
    int on_remote=0;
    int on_local=0;
#ifdef __linux__
    ros::Publisher pub_1;
    ros::NodeHandlePtr nh_;
#endif
    void EventTriggeres(XTLevent event) override;
signals:
private slots:
    void setservice();
#ifdef __linux__
    void setHandle(ros::NodeHandlePtr nh);
#endif
    void switch_control(XTLevent event);
    void startpub();
    void stoppub();



};

#endif // PUB_THREAD_H
