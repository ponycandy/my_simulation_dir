#include "vehiclemanager.h"
#include "VehicleControllerActivator.h"
#include "event/eventype.h"
VehicleManager::VehicleManager(QObject *parent) : QObject(parent)
{
    VehicleControllerActivator::subscribevent(UCSEVENT::MQTTNETSET,this);
    VehicleControllerActivator::subscribevent(UCSEVENT::MQTTSTART,this);
    VehicleControllerActivator::subscribevent(UCSEVENT::MQTTSTOP,this);

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

        vehicle->cilentID_S=event.m_dict.value("cilentID(S)").value<QString>();
        vehicle->host_S=event.m_dict.value("host(S)").value<QString>();
        vehicle->port_S=event.m_dict.value("port(S)").value<QString>();
        vehicle->username_S=event.m_dict.value("username(S)").value<QString>();
        vehicle->password_S=event.m_dict.value("password(S)").value<QString>();
        vehicle->vehiclename=event.m_dict.value("vehiclename").value<QString>();
        vehicle->videoAddress=event.m_dict.value("videoAddress").value<QString>();

        vehicle->setupconnection();

        VideoCoreservice *vidservice_temp=VehicleControllerActivator::getService<VideoCoreservice>("VideoCoreservice");
        VideoCoreservice* vidservice=vidservice_temp->cloneservice();
        videoserviceMap.insert(vehicle->vehiclename,vidservice);
        vidservice->setrtmpPath(vehicle->videoAddress);

        viewer->Addwidget(vidservice->getVideoPlayerWindow(), vehicle->vehiclename,"VideoStream");
        viewer->Addwidget(mapwidget, vehicle->vehiclename,"LocalMap");

        cargroup.insert(vehicle->vehiclename,vehicle);

    }
    if(event.eventname==UCSEVENT::MQTTSTART)
    {
        QMap<QString, SingleVehicleCard*>::iterator itor;
        for (itor = cargroup.begin(); itor != cargroup.end(); ++itor)
        {
            itor.value()->connectall();
        }
    }
    if(event.eventname==UCSEVENT::MQTTSTOP)
    {

        QMap<QString, SingleVehicleCard*>::iterator itor;
        for (itor = cargroup.begin(); itor != cargroup.end(); ++itor)
        {
            itor.value()->disconnect();
        }
        viewer->clearcombox();

    }
}

void VehicleManager::send(QByteArray byteArray, QString vehiclename, QString topicname)
{
    cargroup.value(vehiclename)->send(byteArray,vehiclename+"/"+topicname);
}

VehicleControlservice *VehicleManager::cloneservice()
{
    VehicleManager *vehicle=new VehicleManager;
    return vehicle;
}
