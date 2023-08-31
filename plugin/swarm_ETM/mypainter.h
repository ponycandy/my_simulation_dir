#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QObject>
#include <include/GL_2D/draw_operation.h>
#include <Eigen/Core>
#include <include/GL_2D/GL2Dcommon.h>
#include <ClosePoint.h>
#include <SwarmAgent.h>
#include <SwarmObstacle.h>
class MYpainter : public QObject,public DrawOperation
{
    Q_OBJECT
public:
    explicit MYpainter(QObject *parent = nullptr);
    void draw() override;

    QBrush agent_brush;
    QBrush leader_brush;
     QBrush circle_brush;
    double collision_r;
    Eigen::MatrixXd Targetstate;//x y phi
    Eigen::MatrixXd Leaderstate;//x y phi
public slots:
    void updateTargetpos(double x,double y,double phi);
void updateLeaderpos(double x,double y,double phi);
};

#endif // MYPAINTER_H
