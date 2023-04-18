#include "mypainter.h"
#include "QtDebug"
MYpainter::MYpainter(QObject *parent) : QObject(parent)
{
    agent_brush.setColor(Qt::red);
    agent_brush.setStyle(Qt::SolidPattern);
    close_brush.setColor(Qt::yellow);
    close_brush.setStyle(Qt::SolidPattern);
    obs_brush.setColor(Qt::blue);
    obs_brush.setStyle(Qt::SolidPattern);
    circle_brush.setColor(Qt::black);
    x_pos,omega,penlength,cartwidth,cartheight,pendwidth,phi=0;
    cartwidth=3;
    cartheight=3;
    penlength=10;
    pendwidth=0.2;
}

void MYpainter::draw()
{

    m_animator->brush_painter->setBrush(obs_brush);
    QPolygonF poly;
    poly<<QPointF(x_pos+cartwidth/2,-cartheight/2)
         <<QPointF(x_pos-cartwidth/2,-cartheight/2)
         <<QPointF(x_pos-cartwidth/2,cartheight/2)
         <<QPointF(x_pos+cartwidth/2,cartheight/2);
    m_animator->draw_polygon(poly);
    m_animator->brush_painter->setBrush(agent_brush);
    m_animator->draw_square_oneside(x_pos,0,pendwidth,penlength,phi);



}

void MYpainter::slot_update_state(QVector<double> state_array)
{
    //x_pos,omega,penlength,cartwidth,cartheight,pendwidth
    x_pos=state_array[0];
    omega=state_array[1];
    penlength=state_array[2];
    cartwidth=state_array[3];
    cartheight=state_array[4];
    pendwidth=state_array[5];
    vel=state_array[6];
    phi=state_array[7];
}

void MYpainter::setstate(Eigen::MatrixXd state)
{
    x_pos=state(0,0);
    phi=state(1,0);
    draw();
}
