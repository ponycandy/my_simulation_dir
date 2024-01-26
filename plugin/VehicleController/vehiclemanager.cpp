#include "vehiclemanager.h"
#include "VehicleControllerActivator.h"
#include "event/eventype.h"
VehicleManager::VehicleManager(QObject *parent) : QObject(parent)
{
    VehicleControllerActivator::subscribevent(UCSEVENT::MQTTNETSET,this);
    VehicleControllerActivator::subscribevent(UCSEVENT::MQTTSTART,this);
    VehicleControllerActivator::subscribevent(UCSEVENT::MQTTSTOP,this);

    vehicle_order=0;
    viewer=new CardataViewer;
    coreservice=VehicleControllerActivator::getService<Coreservice>("Coreservice");
    coreservice->addView(UcsDefines::CardataViewer,viewer);
    mapservl=VehicleControllerActivator::getService<MapService>("MapService");
    mapwidget=mapservl->getMapwidget();
}

void VehicleManager::EventTriggeres(XTLevent event)
{
    if(event.eventname==UCSEVENT::MQTTNETSET)
    {
        SingleVehicleCard *vehicle=new SingleVehicleCard;
        cargroup.push_back(vehicle);
        vehicle->vehiclenumber=vehicle_order;

        vehicle->cilentID_S=event.m_dict.value("cilentID(S)").value<QString>();
        vehicle->host_S=event.m_dict.value("host(S)").value<QString>();
        vehicle->port_S=event.m_dict.value("port(S)").value<QString>();
        vehicle->topicname_S=event.m_dict.value("topicname(S)").value<QString>();
        vehicle->username_S=event.m_dict.value("username(S)").value<QString>();
        vehicle->password_S=event.m_dict.value("password(S)").value<QString>();
        vehicle->cilentID_R=event.m_dict.value("cilentID(R)").value<QString>();
        vehicle->host_R=event.m_dict.value("host(R)").value<QString>();
        vehicle->port_R=event.m_dict.value("port(R)").value<QString>();
        vehicle->topicname_R=event.m_dict.value("topicname(R)").value<QString>();
        vehicle->username_R=event.m_dict.value("username(R)").value<QString>();
        vehicle->password_R=event.m_dict.value("password(R)").value<QString>();
        vehicle->vehiclename=event.m_dict.value("vehiclename").value<QString>();
        vehicle->videoAddress=event.m_dict.value("videoAddress").value<QString>();

        vehicle->setupconnection();
        VideoCoreservice *vidservice_temp=VehicleControllerActivator::getService<VideoCoreservice>("VideoCoreservice");
        VideoCoreservice* vidservice=vidservice_temp->cloneservice();
        videoserviceMap.insert(vehicle->vehiclename,vidservice);
        vidservice->setrtmpPath(vehicle->videoAddress);
        vehicle_order++;
        viewer->Addwidget(vidservice->getVideoPlayerWindow(), vehicle->vehiclename,"VideoStream");
        viewer->Addwidget(mapwidget, vehicle->vehiclename,"LocalMap");
    }
    if(event.eventname==UCSEVENT::MQTTSTART)
    {
        int i=cargroup.size();
        for (int j=0;j<i;j++)
        {
            cargroup[j]->connectall();
        }
    }
    if(event.eventname==UCSEVENT::MQTTSTOP)
    {
        int i=cargroup.size();
        for (int j=0;j<i;j++)
        {
            cargroup[j]->disconnect();
        }
        viewer->clearcombox();

    }
}
