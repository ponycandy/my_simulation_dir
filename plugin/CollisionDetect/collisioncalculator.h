#ifndef COLLISIONCALCULATOR_H
#define COLLISIONCALCULATOR_H

#include <QObject>
#include <Eigen/Core>
#include <service/CollisionDetectservice.h>
class collisionCalculator : public QObject,public CollisionDetectservice
{
    Q_OBJECT
public:
    explicit collisionCalculator(QObject *parent = nullptr);
    collison_result polygen_circle_detect(double circle_x, double circle_y, double r, QPolygonF obs) override;
    prj_range circle_projection(double circlex, double circley, double r, Eigen::MatrixXd vec);
    prj_range convex_projection(QPolygonF obs, Eigen::MatrixXd vec);
    double find_min(Eigen::MatrixXd dis,int num);
    double find_max(Eigen::MatrixXd dis,int num);
    double vector_dot(Eigen::MatrixXd ad,Eigen::MatrixXd bd);

signals:

};

#endif // COLLISIONCALCULATOR_H
