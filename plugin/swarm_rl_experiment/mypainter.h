#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QObject>
#include <include/GL_2D/draw_operation.h>
#include <Eigen/Core>
#include <include/GL_2D/GL2Dcommon.h>
#include <ClosePoint.h>
#include <SwarmAgent.h>
class MYpainter : public QObject,public DrawOperation
{
    Q_OBJECT
public:
    explicit MYpainter(QObject *parent = nullptr);
    void draw() override;

    QBrush agent_brush;
    Eigen::MatrixXd ref_mat;
    QMap<int, SwarmAgent *> m_agents;

signals:

};

#endif // MYPAINTER_H
