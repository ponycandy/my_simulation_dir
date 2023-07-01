#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <QObject>
#include "include/GL_2D/draw_operation.h"
#include <Eigen/Core>
#include "PolyParams.h"
class visualize : public QObject,public DrawOperation
{
    Q_OBJECT
public:
    explicit visualize(QObject *parent = nullptr);
    void draw() override;
    void calc_coordinate(int agent,int phase,double time,double &x,double &y);
    QVector<PolyParams> m_polys;
    int agentnum;
    double steptime;
    int dims;
    int point_num;
    int dec_num;
    double resolution;
    QBrush agent_brush;
    Eigen::MatrixXd initstates_of_animals;
    double x_pos;
    double y_pos;

public slots:
    void update_agent(QVector<PolyParams> polys,double finalx,double finaly);

};

#endif // VISUALIZE_H
