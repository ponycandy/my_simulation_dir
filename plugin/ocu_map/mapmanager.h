#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#pragma once

#include <QObject>
#include <service/Mapservice.h>
#include <mapwidget.h>
#include "service/ocu_car_coreservice.h"
#include "graphicsmap.h"
#include "interactivemap.h"
#include "mapoperator.h"
#include "maprouteitem.h"
#include "MapObjectItem.h"
#include "MapRangeRingItem.h"
#include "mappieitem.h"
#include "maprectitem.h"
#include "mapellipseitem.h"
#include "QTime"
#include "mapscutcheonitem.h"
#include "roadmap.h"
#include "mappolygonitem.h"
#include "service/AIinterfaceservice.h"
class MapWidget;

struct positioninfo
{
    QGeoCoordinate cor;
    double direction;
    MapObjectItem *obj;
    MapSuctcheonItem *m_struct;
};

class map_data_collection:public JsonVar
{
public:
    void Internel_2_member() override;
    void member_2_internel() override;
    QVector<Eigen::MatrixXd> coordinatelists;
};


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
    void Add_List_Item(QString field_Name,MapSuctcheonItem *stru);
    void ai_draw_line(QVector<JsonVar *> j);
    void draw_line(QGeoCoordinate start, QGeoCoordinate terminal, int direction, QColor color, double width) override;
    void Add_Object_Item(int ID,QPixmap icon,QGeoCoordinate cor,double direction) override;
    void Update_Object_Item(int ID, QGeoCoordinate cor,double direction) override;
    void choosearea(QColor colour) override;
    QVector<QGeoCoordinate> stopchoosearea() override;
    ~MapManager();

    InteractiveMap* map ;
    MapRouteOperator* rout_selector;
    MapPolygonOperator *area_selector;
    MapPolygonItem *m_polygon_item;
    MapRouteItem *route_item;
    QTimer *timer;
    MapObjectItem *objitem;
    QMap<int, positioninfo> carIDlists;
    roadmap *m_map;
    map_data_collection *reg_ai_data;
    double lat;
    double lon;
    AIinterfaceservice *aiservice;

public slots:
    void slot_start_record_points();
    void slot_stop_record_points();
    void slot_Autonavi_points();
    void slot_Update_coord();

private:

    /**
     * @brief m_mapWidget 地图界面指针
     */
    MapWidget *m_mapWidget;

};
#endif // MAPMANAGER_H
