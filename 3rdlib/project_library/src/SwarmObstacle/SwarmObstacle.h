#ifndef SWARMOBSTACLE_H
#define SWARMOBSTACLE_H
#include "SWARMOBSTACLE_global.h"
#include <QPolygonF>
class SWARMOBSTACLE_EXPORT SwarmObstacle
{
public:
	SwarmObstacle();
    double x_low;
    double x_up;
    double y_low;
    double y_up;
    int ID;
    QPolygonF vertex_map;
    int vertex_num;
private:
};


#endif // SWARMOBSTACLE_H
