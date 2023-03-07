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
}

void MYpainter::draw()
{

    m_animator->brush_painter->setBrush(obs_brush);
    QMap<int, single_obstacle *>::const_iterator iter2 = m_obs.cbegin();
    while (iter2 != m_obs.cend())
    {
        m_animator->draw_polygon(iter2.value()->vertex_map);
        ++iter2;
    }
    QMap<int, Single_agent *>::const_iterator iter1 = m_agents.cbegin();
    while (iter1 != m_agents.cend())
    {
        m_animator->brush_painter->setBrush(agent_brush);
        m_animator->draw_beacon(iter1.value()->state(0,0),iter1.value()->state(1,0),iter1.value()->angle);
        QMap<int, Single_agent*>::const_iterator iter12 = iter1.value()->neib_map.cbegin();
        while (iter12 != iter1.value()->neib_map.cend())
        {
            m_animator->draw_line(iter1.value()->state(0,0),iter1.value()->state(1,0),
                                  iter12.value()->state(0,0),iter12.value()->state(1,0));
            ++iter12;
        }
                m_animator->brush_painter->setBrush(circle_brush);

                m_animator->draw_circle(iter1.value()->state(0,0),iter1.value()->state(1,0),iter1.value()->collision_r);

        m_animator->brush_painter->setBrush(close_brush);
        QMap<int, pos_xy>::const_iterator iter11 = iter1.value()->closepoint_map.cbegin();
        while (iter11 != iter1.value()->closepoint_map.cend())
        {
            m_animator->draw_beacon(iter11.value().x,iter11.value().y,iter11.value().angle);
            ++iter11;
        }
        //        QMap<int, pos_xy>::const_iterator iter12 = iter1.value()->closepoint_map.cbegin();
        //        while (iter12 != iter1.value()->closepoint_map.cend())
        //        {
        //            m_animator->draw_beacon(iter12.value().x,iter12.value().y,iter12.value()->angle);
        //            ++iter12;
        //        }

        ++iter1;
    }


}

void MYpainter::slot_update_state(QMap<int, Single_agent *> agentgroup)
{
    m_agents=agentgroup;
}

void MYpainter::slot_obs_state_update(QMap<int, single_obstacle *> obs_group)
{
    m_obs=obs_group;
}
