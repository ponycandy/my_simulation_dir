#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QObject>
#include <include/GL_2D/draw_operation.h>
#include <Eigen/Core>
#include <include/GL_2D/GL2Dcommon.h>

class MYpainter : public QObject,public DrawOperation
{
    Q_OBJECT
public:
    explicit MYpainter(QObject *parent = nullptr);
    void draw() override;
    QBrush agent_brush;
    QBrush obs_brush;
    Eigen::MatrixXd vehiclepos;
    QVector<pos_xy> pos;
private slots:
    void slot_update_state(Eigen::MatrixXd state);
signals:

};

#endif // MYPAINTER_H
