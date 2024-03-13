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
    map->setTilePath("D:/QT/prjdir/OSGIMODULE/my_simulation_dir/build/Map/StreetMap");
    map->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    //显示一个地图：
    map->setZoomLevel(8);
    QGeoCoordinate cor(116,40);
    map->centerOn(cor);
    //隐藏滚动条：
    map->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    map->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    //设置鼠标中心缩放和鼠标拖动地图：
    map->setDragMode(QGraphicsView::ScrollHandDrag);
    map->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    map->resize(1680,1080);

}

InteractiveMap *MapManager::getMapwidget()
{
    return map;
}

/**
 * @brief MapManager::~MapManager
 */
MapManager::~MapManager()
{
}

