#ifndef ANIMATOR_MANAGER_H
#define ANIMATOR_MANAGER_H
#include <QWidget>
#include "interactivemap.h"
#include "service/Mapservice.h"
#include "controlwidget.h"
#include "service/SwarmSimservice.h"
#include "vehicle.h"
class animator_manager
{
public:
    animator_manager();
    MapService *map_service;
    InteractiveMap *mapwidget;
    ControlWidget *m_control;
    SwarmSimservice *sim_service;
    vehicle *m_vehiclemodel;
};

#endif // ANIMATOR_MANAGER_H
