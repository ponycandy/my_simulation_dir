#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#pragma once

#include <QObject>
#include <service/Mapservice.h>
#include <mapwidget.h>
#include "service/ocu_car_coreservice.h"
#include "graphicsmap.h"
#include "interactivemap.h"
class MapWidget;

class MapManager : public QObject, public MapService
{
    Q_OBJECT
    Q_INTERFACES(MapService)
public:
    /**
     * @brief MapManager
     * @param parent
     */
    explicit MapManager(QObject *parent = nullptr);
    InteractiveMap* getMapwidget() override;
    ~MapManager();

    InteractiveMap* map ;



public slots:


private:

    /**
     * @brief m_mapWidget 地图界面指针
     */
    MapWidget *m_mapWidget;

};
#endif // MAPMANAGER_H
