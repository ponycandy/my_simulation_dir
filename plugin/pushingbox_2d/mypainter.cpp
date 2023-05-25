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
    cartwidth=0.5;
    cartheight=0.5;
    penlength=10;
    pendwidth=0.2;
}

void MYpainter::draw()
{

    m_animator->brush_painter->setBrush(obs_brush);
    QPolygonF poly;
    poly<<QPointF(x_pos+cartwidth/2,y_pos-cartheight/2)
       <<QPointF(x_pos-cartwidth/2,y_pos-cartheight/2)
      <<QPointF(x_pos-cartwidth/2,y_pos+cartheight/2)
     <<QPointF(x_pos+cartwidth/2,y_pos+cartheight/2);
    m_animator->draw_polygon(poly);
    m_animator->brush_painter->setBrush(agent_brush);
    m_animator->draw_square(0,0,0.1,3,0);



}

void MYpainter::slot_update_state(QVector<double> state_array)
{
    //x_pos,omega,penlength,cartwidth,cartheight,pendwidth
    x_pos=state_array[0];
    y_pos=state_array[1];
}
