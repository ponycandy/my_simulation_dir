#ifndef MESSAGECOLLECTOR_H
#define MESSAGECOLLECTOR_H

#include <QObject>
#include <service/Datamanageservice.h>

#include <smartptr.h>


#include <netconfigwidget.h>

#include <service/eventservice.h>


#include "service/ocu_car_coreservice.h"
#include "datacollection.h"

#ifdef __linux__
#include <sensor_msgs/PointCloud.h>
#include <geometry_msgs/Twist.h>
#endif
#include "statusdisplay.h"
class messagecollector : public QObject,public Datamanageservice,public EventService
{
    Q_OBJECT
    Q_INTERFACES(Datamanageservice)
public:
    explicit messagecollector(QObject *parent = nullptr);
    //god damd，这些ros下的东西怎么弄啊......
//    void store(const sensor_msgs::PointCloud data) override;
//    void store(const sensor_msgs::Joy data) override;
//    geometry_msgs::Twist send() override;
    StatusDisplay *display;
    void publishtocloud() override;
    char * copy_buffer(QByteArray data) override;
    void Demux(char *input) override;
    void EventTriggeres(XTLevent event) override;
    Datacollection *m_Data;
    Netconfigwidget *m_widget;
    ocu_car_coreservice *m_service;
    SmartPtr<Datacollection> m_Data_Ptr;
    int flag=0;
    bool displaystatusflag=false;
    bool first_time_display_flag=true;
signals:
    void test_data_pub();

};

#endif // MESSAGECOLLECTOR_H
