#include "messagecollector.h"
#include "DatamanagerActivator.h"
#include <QDebug>
#include "event/OcuEventContants.h"
#include "defines/OcuDefines.h"
#include "service/VehicleControlservice.h"
messagecollector::messagecollector(QObject *parent) : QObject(parent),m_Data(NULL),m_widget(NULL)
{
    flag=0;
    m_Data=new Datacollection;
    m_Data_Ptr.setpointee(m_Data);
    m_widget=new Netconfigwidget;
    DatamanagerActivator::registerservice(this,"Datamanageservice");
    DatamanagerActivator::subscribevent(UcsEventConstants::TOPCI_MENU_CLICKED,this);
    // display=new StatusDisplay;
    // display->update_BatteryHealthy(0);
    // display->update_BatteryTemprature(0);
    // display->update_acc_x(0);
    // display->update_acc_y(0);
    // display->update_acc_z(0);
    // display->update_altitude(0);
    // display->update_latitude(0);
    // display->update_angular_velocity(0);
    // display->update_linear_velocity(0);
    // display->update_motorRPM_1(0);
    // display->update_motorRPM_2(0);
    // display->update_motorRPM_3(0);
    // display->update_motorRPM_4(0);
    // display->update_pitch(0);
    // display->update_roll(0);
    // display->update_yaw(0);

    //initialization

}
#ifdef __linux__
void messagecollector::store(const sensor_msgs::PointCloud data)
{
    //leave it clean for now
    //use mutex object to store data
    qDebug()<<"one of them"<<data.points[1].x;
}
void messagecollector::store(const sensor_msgs::Joy data)
{

    m_Data_Ptr->set_local_cmd(data.axes[3],data.axes[1]);
}
geometry_msgs::Twist messagecollector::send()
{
    return      m_Data_Ptr->send_local_cmd();
}
#endif




void messagecollector::publishtocloud()
{

}

char *messagecollector::copy_buffer(QByteArray data)
{
    data.resize(4);data[0]=0x01;data[1]=0x02;data[0]=0x03;data[1]=0x04;

    return data.data();
}

void messagecollector::Demux(char *input)
{

}

void messagecollector::EventTriggeres(XTLevent event)
{
    if(flag==0)
    {
        m_service=DatamanagerActivator::getService<ocu_car_coreservice>("ocu_car_coreservice");
        m_service->addView(UcsDefines::NETCONFIG_INTERFACE,m_widget);
        flag=1;

    }
    if(event.m_dict.value("property").toString()==UcsEventConstants::NETCONFIG)
    {
        m_service->changeView(UcsDefines::NETCONFIG_INTERFACE);
    }

}

