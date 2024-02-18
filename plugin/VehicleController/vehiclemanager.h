#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H


#include <QObject>
#include <QWidget>
#include "service/eventservice.h"
#include "singlevehiclecard.h"
#include "cardataviewer.h"
#include "service/Coreservice.h"
#include "service/VideoCoreservice.h"
#include "service/Mapservice.h"
#include "service/VehicleControlservice.h"
class VehicleManager:public QObject,public EventService,public VehicleControlservice
{
    Q_OBJECT
public:
    explicit VehicleManager(QObject *parent = nullptr);
    void  EventTriggeres(XTLevent event) override;
    void send(QByteArray byteArray,QString vehiclename,QString topicname) override;
    VehicleControlservice *cloneservice() override;
    QMap<QString,SingleVehicleCard*> cargroup;

    QMap<QString,VideoCoreservice*> videoserviceMap;
    int vehicle_order;
    CardataViewer *viewer;
    MapService *mapservl;
    InteractiveMap *mapwidget;
    Coreservice *coreservice;
};

#endif // VEHICLEMANAGER_H
