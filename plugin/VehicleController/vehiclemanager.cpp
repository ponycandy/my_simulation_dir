#include "vehiclemanager.h"
#include "VehicleControllerActivator.h"
#include "event/eventype.h"
#include "event/OcuEventContants.h"
#include "jetsonnanoDATA/jetsonnanoDATA.h"
#include "include/OSGIEVENT.h"

VehicleManager::VehicleManager(QObject *parent) : QObject(parent)
{
    VehicleControllerActivator::subscribevent(UCSEVENT::MQTTNETSET,this);
    VehicleControllerActivator::subscribevent(UCSEVENT::MQTTSTART,this);
    VehicleControllerActivator::subscribevent(UCSEVENT::MQTTSTOP,this);
    VehicleControllerActivator::subscribevent(UcsEventConstants::TOPCI_MENU_CLICKED,this);

    viewer=new CardataViewer;
    // coreservice=VehicleControllerActivator::getService<Coreservice>("Coreservice");
    // coreservice->addView(UcsDefines::CardataViewer,viewer);

    car_core_service=VehicleControllerActivator::getService<ocu_car_coreservice>("ocu_car_coreservice");
    //这里把所有其它的界面都添加为本widget


    car_core_service->addView(UcsDefines::UCS_VIEW_KIND_MAIN,viewer);
    car_core_service->changeView(UcsDefines::UCS_VIEW_KIND_MAIN);

    mapservl=VehicleControllerActivator::getService<MapService>("MapService");
    mapwidget=mapservl->getMapwidget();


    simservice=VehicleControllerActivator::getService<SwarmSimservice>("SwarmSimservice");
    if(simservice!=NULL)
    {
        m_simulation_widget=simservice->getwidgetoperator()->getwidget();
    }

}

void VehicleManager::EventTriggeres(XTLevent event)
{
    if(event.eventname==UCSEVENT::MQTTNETSET)
    {
        SingleVehicleCard *vehicle=new SingleVehicleCard;

        vehicle->cilentID_S="server"+event.m_dict.value("vehiclename").value<QString>();
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
        //状态显示绑定到videoviewer上
        initilizevideostatus(vidservice->getVideoPlayerWindow(),vehicle->vehiclename);

        viewer->Addwidget(mapwidget, vehicle->vehiclename,"LocalMap");
        QWidget *temp_m_simulation_widget=new QWidget;
        temp_m_simulation_widget->setContentsMargins(0,0,0,0);
        temp_m_simulation_widget->resize(1780,1080);
        if(m_simulation_widget)
        {
            m_simulation_widget->resize(1780,1080);
            m_simulation_widget->setContentsMargins(0,0,0,0);
            m_simulation_widget->move(0,0);
            m_simulation_widget->setParent(temp_m_simulation_widget);
            viewer->Addwidget(temp_m_simulation_widget, vehicle->vehiclename,"SimulationAnimation");
        }
        viewer->comboBox->setCurrentText(vehicle->vehiclename);
        viewer->comboBox_2->setCurrentText("LocalMap");
        viewer->comboxframe->hide();

        cargroup.insert(vehicle->vehiclename,vehicle);
        car_ID_2_vehiclename.push_back(vehicle->vehiclename);

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
    if(event.eventname==UcsEventConstants::TOPCI_MENU_CLICKED)
    {
        QString name=event.m_dict.value("property").toString();
        if(name==UcsEventConstants::SOURCESWITCH)
        {
//一次按下显示
            viewer->display_combox();
        }
        if(name==UcsEventConstants::COMMANDLINEEXEC)
        {

        }
    }

    if(event.m_dict.value("property").toString()==UcsEventConstants::DISPLAYSTATUS)
    {
        if(first_time_display_flag==true)
        {
         //   AddHUD_2_controler(display,100,100);
            first_time_display_flag=false;

        }
        else
        {

        }
        if(displaystatusflag==true)
        {
            displaystatusflag=false;//显示
            QMap<QString, StatusDisplay*>::iterator itor;
            for (itor = statusdisplaymap.begin(); itor != statusdisplaymap.end(); ++itor)
            {
                itor.value()->show();
            }
        }
        else
        {

            displaystatusflag=true;
            QMap<QString, StatusDisplay*>::iterator itor;
            for (itor = statusdisplaymap.begin(); itor != statusdisplaymap.end(); ++itor)
            {
                itor.value()->hide();
            }

        }

        // m_service->changeView(UcsDefines::NETCONFIG_INTERFACE);
    }

}

void VehicleManager::initilizevideostatus(QWidget *wid, QString vehiclename)
{
    StatusDisplay *display=new StatusDisplay;
    display->setParent(wid);
    display->setWindowFlags(Qt::WindowFlags());
    display->setGeometry(viewer->x()+1000,viewer->y()+300,display->width(),display->height());
    statusdisplaymap.insert(vehiclename,display);
    display->update_BatteryHealthy(0);
    display->update_BatteryTemprature(0);
    display->update_acc_x(0);
    display->update_acc_y(0);
    display->update_acc_z(0);
    display->update_longitude(0);
    display->update_altitude(0);
    display->update_latitude(0);
    display->update_angular_velocity(0);
    display->update_linear_velocity(0);
    display->update_motorRPM_1(0);
    display->update_motorRPM_2(0);
    display->update_motorRPM_3(0);
    display->update_motorRPM_4(0);
    display->update_pitch(0);
    display->update_roll(0);
    display->update_yaw(0);
}

void VehicleManager::sendVehicleCommand(int ID, double linear, double omega)
{
    jetson::motioncommand mocmd;
    mocmd.linear=linear;
    mocmd.omega=omega;
    std::string data=Autoserialization(mocmd);
    QString vehiclename=car_ID_2_vehiclename.value(ID);
    send(QByteArray::fromStdString(data),vehiclename,"motioncommand");
}

void VehicleManager::AddHUD_2_controler(QFrame *wid,double x,double y)
{
    widgetinfos info;
    info.x=x;
    info.y=y;
    info.wid=wid;
    viewer->all_overlays.push_back(info);
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

void VehicleManager::showstartwindow(bool)
{

}
