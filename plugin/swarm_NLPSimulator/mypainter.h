#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QObject>
#include <include/GL_2D/draw_operation.h>
#include <Eigen/Core>
#include <include/GL_2D/GL2Dcommon.h>
#include <ClosePoint.h>
#include <SwarmAgent.h>
#include <SwarmObstacle.h>
struct tripR
{
    double x;
    double y;
    double r;
};
class MYpainter : public QObject,public DrawOperation
{
    Q_OBJECT
public:
    explicit MYpainter(QObject *parent = nullptr);
    void draw() override;

    int obsnum;
    int pointnum;
    QMap<int , tripR > OBSmap;
    Eigen::MatrixXd targetmat;
QBrush obs_brush;
    QBrush traj_brush;
public slots:
    void updateTargetpos(Eigen::MatrixXd target);
};

#endif // MYPAINTER_H
