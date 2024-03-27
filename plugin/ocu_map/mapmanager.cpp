#include "mapmanager.h"
#include "ocu_mapActivator.h"
#include "defines/OcuDefines.h"
/**
 * @brief MapManager::MapManager
 * @param parent
 */
MapManager::MapManager(QObject *parent)
    : QObject(parent)
    , m_mapWidget(NULL)
{
    /** 注册地图服务*/
    // m_mapWidget=new MapWidget;
    //目前问题不大，就是需要写一下地图的交互逻辑...


    map = new InteractiveMap;
    map->setTilePath("D:/QT/prjdir/OSGIMODULE/my_simulation_dir/build/Map/Njmap/map/map");
    map->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    //显示一个地图：

    map->setZoomLevel(15);
    QGeoCoordinate cor(39.959,116.321);//北纬--东经
    map->centerOn(cor);
    //隐藏滚动条：
    map->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    map->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    //设置鼠标中心缩放和鼠标拖动地图：
    map->setDragMode(QGraphicsView::ScrollHandDrag);
    map->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    map->resize(1680,1080);

    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_Update_coord()));
}

InteractiveMap *MapManager::getMapwidget()
{
    return map;
}

void MapManager::Add_List_Item(QString field_Name, MapSuctcheonItem *stru)
{
    stru->setBackBrush(QColor(30,144,255, 200));
    stru->addField(field_Name,true);
    stru->setValue(field_Name,"      " );
    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    QFont serifFont("Times", 20, QFont::Bold);
    stru->setFieldPen(field_Name, pen);
    stru->setValuePen(field_Name, pen);
    stru->setFieldFont(field_Name,serifFont);
    stru->setValueFont(field_Name,serifFont);
}

void MapManager::Add_Object_Item(int ID, QPixmap icon, QGeoCoordinate cor, double direction)
{
    MapObjectItem *obj=new MapObjectItem;
    obj->setText(QString::number(ID));
    positioninfo pos;
    pos.cor=cor;
    pos.direction=direction;
    pos.obj=obj;



    obj->setCoordinate(cor);
    obj->setIcon(icon);
    map->scene()->addItem(obj);
    MapSuctcheonItem *mstruct= obj->getMapTabel();
    delete mstruct;
    MapSuctcheonItem *m_new_struct=new MapSuctcheonItem(obj);
    pos.m_struct=m_new_struct;
    Add_List_Item("标号",m_new_struct);
    m_new_struct->setBackBrush(QColor(30,144,255, 200));
    m_new_struct->addField(u8"标号",true);
    m_new_struct->setValue(u8"标号","      "+QString::number(ID));
    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    QFont serifFont("Times", 20, QFont::Bold);
    m_new_struct->setFieldPen(u8"标号", pen);
    m_new_struct->setValuePen(u8"标号", pen);
    m_new_struct->setFieldFont(u8"标号",serifFont);
    m_new_struct->setValueFont(u8"标号",serifFont);


    carIDlists.insert(ID,pos);
}

void MapManager::Update_Object_Item(int ID, QGeoCoordinate cor, double direction)
{
    positioninfo pos=carIDlists.value(ID);
    pos.cor=cor;
    pos.obj->setCoordinate(pos.cor);
    pos.direction=direction;
}

void MapManager::choosearea(QColor colour)
{
    area_selector=new MapPolygonOperator;
    map->pushOperator(area_selector);

    m_polygon_item=new MapPolygonItem;

    QBrush obstacle_brush;
    obstacle_brush.setColor(colour);
    obstacle_brush.setStyle(Qt::SolidPattern);
    m_polygon_item->setBrush(obstacle_brush);
    m_polygon_item->setEditable(true);
    area_selector->takeOver(m_polygon_item);
    area_selector->scene()->addItem(m_polygon_item);
}

QVector<QGeoCoordinate> MapManager::stopchoosearea()
{
    QVector<QGeoCoordinate> pointsmap_2_launch;
    pointsmap_2_launch=m_polygon_item->points();
    map->popOperator();
    return pointsmap_2_launch;
}

/**
 * @brief MapManager::~MapManager
 */
MapManager::~MapManager()
{
}

void MapManager::slot_start_record_points()
{
    qDebug()<<"开始选点";
    // rout_selector
    rout_selector=new MapRouteOperator;
    map->pushOperator(rout_selector);
    route_item=new MapRouteItem;
    rout_selector->takeOver(route_item);
    rout_selector->scene()->addItem(route_item);
    route_item->setMoveable(true);
    route_item->setExclusive(true);
    route_item->setCheckable(true);
    // map->setOperator(new MapRouteOperator);
}

void MapManager::slot_stop_record_points()
{
    qDebug()<<"停止选点";

    QVector<MapObjectItem*> pointsmap;
    QVector<QGeoCoordinate> pointsmap_2_launch;
    pointsmap=route_item->points();

    QVector<MapObjectItem*>::iterator iter_pointsmap;
    int i=0;
    for (iter_pointsmap=pointsmap.begin();iter_pointsmap!=pointsmap.end();iter_pointsmap++)
    {
        QGeoCoordinate corrdinate=(*iter_pointsmap)->coordinate();
        qDebug()<<"标号"<<QString::number(i)<<" 纬度："<<corrdinate.latitude()<<" 经度："<<corrdinate.longitude();
        i++;
        pointsmap_2_launch.push_back(corrdinate);
    }

    map->popOperator();
}

void MapManager::slot_Autonavi_points()
{
    qDebug()<<"开始导航";
    //假设位置为00，然后平移中心到最近的位置，接下来将所有的二维点格转为经纬度
    // map->pushOperator(new MapPolygonOperator);
    // MapObjectOperator *mapobj=new MapObjectOperator;
    // MapObjectItem *mapItem=new MapObjectItem;
    // map->pushOperator(mapobj);

    // mapobj->takeOver(mapItem);

    // auto range = new MapRangeRingItem;	// 距离环
    // range->setCoordinate({39.959,116.321});
    // range->setRadius(90);
    // map->scene()->addItem(range);
    // range->setRadius(20);

    // MapPieItem *pie=new MapPieItem;
    // pie->setCoordinate({39.959,116.321});
    // pie->setRadius(100);
    // map->scene()->addItem(pie);


    // MapEllipseItem *RectItem=new MapEllipseItem;
    // RectItem->setCenter({39.959,116.321});
    // map->scene()->addItem(RectItem);

    objitem=new MapObjectItem;
    lat=39.959;
    lon=116.321;
    objitem->setCoordinate({lat,lon});
    QPixmap picture(":/blue.png");
    objitem->setIcon(picture);
    map->scene()->addItem(objitem);
    timer->start(30);
    MapSuctcheonItem *mstruct= objitem->getMapTabel();
    delete mstruct;
    //如何通过命令行添加一个无人车？
}

void MapManager::slot_Update_coord()
{
    //这个是不可能精准的
    //因为地面本然就不是球面，所以，直接将角速度、线速度、方向角
    //都转化为经纬度的转化就好了
    //精度1度85.39km，1m/s向东对应 1.1710973181871413514463051879611e-5
    //纬度1度111km 1m/s向北对应 9.009009009009009009009009009009e-6
    lat+=9.009009009009009009009009009009e-6 /(1000/30);//向北1m/s，算上30ms的时间update
    lon+=1.1710973181871413514463051879611e-5 / (1000/30);//向东1m/s
    objitem->setCoordinate({lat,lon});
}

