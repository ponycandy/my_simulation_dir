
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
    /**
     * @brief 圈选区域
     * @param 圈选区域的颜色
     * @return
     */
    virtual void choosearea(QColor colour)=0;
    /**
     * @brief 摘取圈选区域的顶点
     * @param
     * @return
     */
    virtual QVector<QGeoCoordinate> stopchoosearea()=0;
    /**
     * @brief 添加一个标识用以标识无人车
     * @param 无人车ID  标识用的图像 坐标 方向角
     * @return
     */
    virtual void Add_Object_Item(int ID,QPixmap icon,QGeoCoordinate cor,double direction)=0;
    /**
     * @brief 更新已有车辆的状态
     * @param 无人车ID  坐标 方向角
     * @return
     */
    virtual void Update_Object_Item(int ID, QGeoCoordinate cor,double direction)=0;

};
#define MapService_iid "MapService"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(MapService,MapService_iid  )
QT_END_NAMESPACE

#endif

