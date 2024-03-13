#ifndef MYANIMATOR_H
#define MYANIMATOR_H
#include "service/Animateservice.h"
#include "include/GL_2D/draw_operation.h"
#include "SwarmAgent.h"
#include "SwarmObstacle.h"
class MyAnimator:public DrawOperation
{
public:
    MyAnimator();
    void draw() override;

    QBrush agent_brush;
    QBrush obs_brush;
    QBrush close_brush;
    QBrush circle_brush;


    QPolygonF obstacle;

    QPolygonF obstacle1;
    Eigen::MatrixXd agent_mat;
    QMap<int, SwarmObstacle *> m_obs;
    QMap<int, SwarmAgent *> m_agents;
private slots:
    void slot_update_state(QMap<int,SwarmAgent*> agentgroup);
    void slot_obs_state_update(QMap<int,SwarmObstacle*> obs_group);
};

#endif // MYANIMATOR_H
