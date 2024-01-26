
#ifndef MAPSERVICE_H
#define MAPSERVICE_H
#pragma once
#include <QObject>


#include <QtPlugin>
#include "interactivemap.h"
class MapService
{
public:
    virtual ~MapService(){}
    virtual InteractiveMap* getMapwidget()=0;
    //显示哪种地图，我们按照难度最小的那种来
    //那么自然就是雷达点云或者地理地图比较好了
    //雷达点云地图可以借用学弟的成果，更快也更美观
    //完全可以采用另起一个线程的方式
    //不行的话那就openGL来（需要克服相机坐标系的问题）


};
#define MapService_iid "MapService"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(MapService,MapService_iid  )
QT_END_NAMESPACE

#endif

