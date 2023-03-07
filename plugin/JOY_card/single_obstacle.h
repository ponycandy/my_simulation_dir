#ifndef SINGLE_OBSTACLE_H
#define SINGLE_OBSTACLE_H

#include <QMap>
#include <include/GL_2D/GL2Dcommon.h>
#include <QPolygonF>
class single_obstacle
{
public:
    single_obstacle();
    double x_low;
    double x_up;
    double y_low;
    double y_up;
    int ID;
    QPolygonF vertex_map;
    int vertex_num;

};

#endif // SINGLE_OBSTACLE_H
