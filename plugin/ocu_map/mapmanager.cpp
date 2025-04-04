#include "mapmanager.h"
#include "ocu_mapActivator.h"
#include "defines/OcuDefines.h"
#include "maplineitem.h"
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
    map->setTilePath("D:/Qt/prjspace/modulesystem/my_simulation_dir/build/googlemaps/hybrid");
    map->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    //显示一个地图：

    map->setZoomLevel(15);
    QGeoCoordinate cor(41.29732,119.40579);//北纬--东经
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
    //接下来绘制路网
    m_map=new roadmap;
    m_map->read_roadmap("D:/Qt/prjspace/modulesystem/my_simulation_dir/build/googlemaps/way_point.txt");
    //功能测试


    for(auto ed : m_map->edges)
    {
        int i=0;
        EdgePoint start=ed[0];
        for(auto ps : ed)
        {
            if(i==0)
            {
                i++;
                continue;
            }
            else
            {
                EdgePoint terminal=ps;
                QGeoCoordinate cor_1(start.wd,start.jd);
                QGeoCoordinate cor_2(terminal.wd,terminal.jd);
                draw_line(cor_1,cor_2,1,QColor(255,0,0,125),5);
                start=terminal;
            }

        }
    }
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

void MapManager::ai_draw_line(QVector<JsonVar *> j)
{
    //实例
    //    {
    //        "function_name": "draw_line",
    //        "args": [
    //            {"type": "value", "value": [矩阵描述]},点1，类型Eigen::matrixXd，内容为经纬度
    //            {"type": "value", "value": [矩阵描述]},点2，类型Eigen::matrixXd，内容为经纬度
    //            {"type": "value", "value": ["direction":??,"color":??(四元组，rgba),"width":"??"]},线的类型（双向，正向，无箭头）
    //        ]
    //    }
    Eigen::MatrixXd p1;
    Eigen::MatrixXd p2;
    int direction;
    Eigen::MatrixXd color;
    double width;
    from_json(j[0]->get(),p1);
    from_json(j[1]->get(),p2);
    direction=(j[3]->get())["direction"].get<int>();
    from_json((j[3]->get())["color"],color);
    from_json((j[3]->get())["width"],width);
    QGeoCoordinate start(p1(0,0),p1(1,0));
    QGeoCoordinate terminal(p2(0,0),p2(1,0));
    QColor qcolor;
    qcolor.setRgb(color(0,0),color(1,0),color(2,0),color(3,0));
    draw_line(start,terminal,direction,qcolor,width);
}

void MapManager::draw_line(QGeoCoordinate start, QGeoCoordinate terminal, int direction, QColor color, double width)
{
    MapLineItem *lineitem=new MapLineItem;
    lineitem->setStartPoint(start);
    lineitem->setEndPoint(terminal);
    lineitem->setLineWidth(width);
    lineitem->setLinecolor(color);
    map->scene()->addItem(lineitem);
}

void MapManager::Add_Object_Item(int ID, QPixmap icon, QGeoCoordinate cor, double direction)
{
    //地图的通用绘制流程（不使用操作器）
    //创建绘图对象MAP_XXX_ITEM obj
    //直接添加绘图对象到地图上map->scene->additem(obj)
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
    Add_List_Item("icon",m_new_struct);
    m_new_struct->setBackBrush(QColor(30,144,255, 200));
    m_new_struct->addField(u8"icon",true);
    m_new_struct->setValue(u8"icon","      "+QString::number(ID));
    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    QFont serifFont("Times", 20, QFont::Bold);
    m_new_struct->setFieldPen(u8"icon", pen);
    m_new_struct->setValuePen(u8"icon", pen);
    m_new_struct->setFieldFont(u8"icon",serifFont);
    m_new_struct->setValueFont(u8"icon",serifFont);


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
    //地图的通用绘制流程（使用操作器）
    //创建绘图对象MAP_XXX_item
    //创建操作器Map_XXX_Operator
    //绑定操作器到地图里面pushOperator
    //绑定绘图对象到操作器上takeOver
    //通过操作器添加绘图对象到地图上->scene->additem
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
    qDebug()<<"starting picking points";
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
    qDebug()<<"stop picking points";

    QVector<MapObjectItem*> pointsmap;
    QVector<QGeoCoordinate> pointsmap_2_launch;
    pointsmap=route_item->points();

    QVector<MapObjectItem*>::iterator iter_pointsmap;
    int i=0;
    for (iter_pointsmap=pointsmap.begin();iter_pointsmap!=pointsmap.end();iter_pointsmap++)
    {
        QGeoCoordinate corrdinate=(*iter_pointsmap)->coordinate();
        qDebug()<<"beacon"<<QString::number(i)<<" lat:"<<corrdinate.latitude()<<" lon:"<<corrdinate.longitude();
        i++;
        pointsmap_2_launch.push_back(corrdinate);
    }

    map->popOperator();
}

void MapManager::slot_Autonavi_points()
{
    qDebug()<<"Nvigation";
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
//    //这个是不可能精准的
//    //因为地面本然就不是球面，所以，直接将角速度、线速度、方向角
//    //都转化为经纬度的转化就好了
//    //精度1度85.39km，1m/s向东对应 1.1710973181871413514463051879611e-5
//    //纬度1度111km 1m/s向北对应 9.009009009009009009009009009009e-6
//    lat+=9.009009009009009009009009009009e-6 /(1000/30);//向北1m/s，算上30ms的时间update
//    lon+=1.1710973181871413514463051879611e-5 / (1000/30);//向东1m/s
//    objitem->setCoordinate({lat,lon});
}


void map_data_collection::Internel_2_member()
{

}

void map_data_collection::member_2_internel()
{

}
