#include "mypainter.h"
#include "QtDebug"
MYpainter::MYpainter(QObject *parent) : QObject(parent)
{
    agent_brush.setColor(Qt::red);
    agent_brush.setStyle(Qt::SolidPattern);

    obs_brush.setColor(Qt::blue);
    obs_brush.setStyle(Qt::SolidPattern);
    vehiclepos.resize(3,1);
    vehiclepos.setZero();

}

void MYpainter::draw()
{

    m_animator->brush_painter->setBrush(obs_brush);
    QPolygonF poly;
    poly << QPointF(0.0, 1.0) << QPointF(2.0, 1.0)<< QPointF(1,2);
    m_animator->draw_polygon(poly);
    for(int i=0;i<pos.size()-1;i++)
    {
        pos_xy startp=pos.value(i);
        pos_xy endp=pos.value(i+1);
        m_animator->draw_line(startp.x,startp.y,endp.x,endp.y);
    }


    m_animator->brush_painter->setBrush(agent_brush);
    m_animator->draw_beacon(vehiclepos(0,0),vehiclepos(1,0),vehiclepos(2,0));



}

void MYpainter::slot_update_state(Eigen::MatrixXd state)
{
    vehiclepos=state;
}
