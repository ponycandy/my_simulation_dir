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

class VehicleManager:public QObject,public EventService
{
    Q_OBJECT
public:
    explicit VehicleManager(QObject *parent = nullptr);
    void  EventTriggeres(XTLevent event) override;
    QVector<SingleVehicleCard*> cargroup;
    QMap<QString,VideoCoreservice*> videoserviceMap;
    int vehicle_order;
    CardataViewer *viewer;
    MapService *mapservl;
    InteractiveMap *mapwidget;
    Coreservice *coreservice;
};

#endif // VEHICLEMANAGER_H
