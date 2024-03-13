#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H


#include <QObject>
#include <QWidget>
#include "service/eventservice.h"
#include "singlevehiclecard.h"
#include "cardataviewer.h"
#include "service/Coreservice.h"
#include "service/ocu_car_coreservice.h"
#include "service/VideoCoreservice.h"
#include "service/Mapservice.h"
#include "statusdisplay.h"
#include "service/VehicleControlservice.h"
class VehicleManager:public QObject,public EventService,public VehicleControlservice
{
    Q_OBJECT
public:
    explicit VehicleManager(QObject *parent = nullptr);
    void  EventTriggeres(XTLevent event) override;
    void initilizevideostatus(QWidget *wid,QString vehiclename);
    void AddHUD_2_controler(QFrame *wid,double x,double y) override;
    void send(QByteArray byteArray,QString vehiclename,QString topicname) override;
    VehicleControlservice *cloneservice() override;
    QMap<QString,SingleVehicleCard*> cargroup;

    QMap<QString,VideoCoreservice*> videoserviceMap;
    QMap<QString ,StatusDisplay*> statusdisplaymap;
    int vehicle_order;
    bool first_time_display_flag=true;
    bool displaystatusflag=true;
  //  StatusDisplay *display;透视显示内容，但是有显示规则
    CardataViewer *viewer;
    MapService *mapservl;
    InteractiveMap *mapwidget;
    Coreservice *coreservice;
    ocu_car_coreservice *car_core_service;
};

#endif // VEHICLEMANAGER_H
