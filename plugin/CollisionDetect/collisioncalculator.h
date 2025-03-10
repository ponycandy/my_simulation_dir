#ifndef COLLISIONCALCULATOR_H
#define COLLISIONCALCULATOR_H

#include <QObject>
#include <Eigen/Core>
#include <service/CollisionDetectservice.h>
struct triple_abc
{
    double a;
    double b;
    double c;
};
class collisionCalculator : public QObject,public CollisionDetectservice
{
    Q_OBJECT
public:
    explicit collisionCalculator(QObject *parent = nullptr);
    collison_result polygen_circle_detect(double circle_x, double circle_y, double r, QPolygonF obs) override;
    collison_result2 polygen_line_segment_detect(Eigen::MatrixXd &Point_a0,Eigen::MatrixXd &Point_a1,QPolygonF &obs) override;
    prj_range circle_projection(double circlex, double circley, double r, Eigen::MatrixXd vec);
    prj_range convex_projection(QPolygonF obs, Eigen::MatrixXd vec);
    prj_range Line_projection(double startx,double starty,
                              double endx,double endy,Eigen::MatrixXd vec);

    double find_min(Eigen::MatrixXd dis,int num);
    double find_max(Eigen::MatrixXd dis,int num);
    double vector_dot(Eigen::MatrixXd ad,Eigen::MatrixXd bd);

signals:

};

#endif // COLLISIONCALCULATOR_H
