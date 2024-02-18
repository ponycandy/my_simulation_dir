#include "messagemanager.h"
#include "testvehiclecontrollerActivator.h"
#include "jetsonnanoDATA/jetsonnanoDATA.h"
#include "Mqttmessenger/Mqttmessenger.h"
messagemanager::messagemanager(QObject *parent)
    : QObject{parent}
{

    m_service=testvehiclecontrollerActivator::getService<VehicleControlservice>("VehicleControlservice");
    m_wid=new controllerwidget;
    connect(m_wid,SIGNAL(send_one()),this,SLOT(nowsendone()));
    m_wid->show();
}

void messagemanager::nowsendone()
{
    jetson::motioncommand cmd;
    cmd.linear=2.0;
    cmd.omega=1.0;
    mqtt_send(m_service,cmd,"motioncommand","jetson_nano_2");
}
