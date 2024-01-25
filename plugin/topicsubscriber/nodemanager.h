#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <QObject>
#include <QTimer>

#include <service/Datamanageservice.h>
#include <service/ocu_car_coreservice.h>
#include <QThread>
#include <listen_thread.h>
#include <service/eventservice.h>
#include <event/eventype.h>
#include <pub_thread.h>
#include <rosnodemanager.h>
#include "singleshot.h"
#include "ros_rviz_widget.h"

#ifdef __linux
#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/Joy.h>
#endif
class nodemanager : public QObject,public EventService
{
    Q_OBJECT
    QThread workingthread;
    QThread workingthread2;
public:
    explicit nodemanager(QObject *parent = nullptr);
#ifdef __linux__
    void chatterCallback(const sensor_msgs::PointCloud data);
    void chatterCallback1(const sensor_msgs::Joy data);
    void vehicle1_auto_topic_callback(const geometry_msgs::Twist data);
    void vehicle2_auto_topic_callback(const geometry_msgs::Twist data);
    ros::Subscriber sub0;
    ros::Subscriber sub1;
    ros::Subscriber sub2;
    ros::Subscriber sub3;
    ros::NodeHandlePtr nh_;
    ros::V_string v_nodes;
#endif
    void init_node();

    Datamanageservice *m_datamanager;
    ocu_car_coreservice *m_car_core_service;
    ros_rviz_widget *rviz_widget;
    listen_thread *m_thread;
    pub_thread *m_thread2;

    void EventTriggeres(XTLevent event) override;
    ROSnodemanager *m_rosview;
    Singleshot *m_pub_once;

private:

    QTimer *ros_timer;

    QStringList m_list;
    QString state_Nokl;
signals:
    void start_node();
    void stop_node();
    #ifdef __linux__
    void sig_setHandle(ros::NodeHandlePtr);
    #endif
    void sig_setservice();
    void sig_start_pubthread();
    void sig_switch_control(XTLevent event);
    void sig_start_pubthread_remote();
    void sig_start_pubthread_local();
    void sig_stop_pubthread();


private slots:
    void spinOnce();
    void slotsig_start_pubthread_remote();
    void slotsig_start_pubthread_local();

    void slotsig_stop_pubthread();




signals:

};

#endif // NODEMANAGER_H
