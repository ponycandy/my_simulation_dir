#include "mypainter.h"
#include "QtDebug"
#include "xmlcore.h"

MYpainter::MYpainter(QObject *parent) : QObject(parent)
{
    xmlCore xmlreader("./config/swarm/swarm.xml");
    finalstate.resize(4,1);
    xmlreader.xmlRead("Gamastate",finalstate);
    agent_brush.setColor(Qt::green);
    agent_brush.setStyle(Qt::SolidPattern);
}

void MYpainter::draw()
{


    m_animator->brush_painter->setBrush(agent_brush);
    m_animator->draw_beacon(finalstate(0,0),finalstate(1,0),0);



}
