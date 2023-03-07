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
    QBrush close_brush;
    QBrush circle_brush;


    QPolygonF obstacle;

    QPolygonF obstacle1;
    Eigen::MatrixXd agent_mat;
    QMap<int, single_obstacle *> m_obs;
    QMap<int, Single_agent *> m_agents;
private slots:
    void slot_update_state(QMap<int,Single_agent*> agentgroup);
    void slot_obs_state_update(QMap<int,single_obstacle*> obs_group);
signals:

};

#endif // MYPAINTER_H
