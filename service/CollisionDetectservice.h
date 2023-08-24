
#ifndef COLLISIONDETECTSERVICE_H
#define COLLISIONDETECTSERVICE_H

#include <QObject>
#include <include/GL_2D/GL2Dcommon.h>
class CollisionDetectservice
{
public:
    virtual ~CollisionDetectservice(){}
    virtual collison_result polygen_circle_detect(double circle_x, double circle_y, double r, QPolygonF obs)=0;
    virtual collison_result2 polygen_line_segment_detect(Eigen::MatrixXd &Point_a0,Eigen::MatrixXd &Point_a1,QPolygonF &obs)=0;
    //输入为线段起始点
};
#define CollisionDetectservice_iid "CollisionDetectservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(CollisionDetectservice,CollisionDetectservice_iid  )
QT_END_NAMESPACE

#endif

