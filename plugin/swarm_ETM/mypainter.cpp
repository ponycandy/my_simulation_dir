#include "mypainter.h"
#include "QtDebug"
#include "xmlcore.h"
#include "swarm_ETMActivator.h"
MYpainter::MYpainter(QObject *parent) : QObject(parent)
{
    xmlCore xmlreader("./config/swarmInception/swarm.xml");
    xmlreader.xmlRead("collision_r",collision_r);
    circle_brush.setColor(Qt::black);
    Targetstate.resize(3,1);
    Targetstate.setZero();
    Leaderstate.resize(3,1);
    Leaderstate.setZero();
    agent_brush.setColor(Qt::darkGreen);
    agent_brush.setStyle(Qt::SolidPattern);

    leader_brush.setColor(Qt::black);
    leader_brush.setStyle(Qt::SolidPattern);

    swarm_ETMActivator::subscribeslot(this,SLOT(updateTargetpos(double,double,double))
                                                                   ,"Targetstateupdatesig",
                                                                   Qt::QueuedConnection);


}

void MYpainter::draw()
{


    m_animator->brush_painter->setBrush(agent_brush);
    m_animator->draw_beacon(Targetstate(0,0),Targetstate(1,0),Targetstate(2,0));



}

void MYpainter::updateTargetpos(double x, double y, double phi)
{
    Targetstate(0,0)=x;
    Targetstate(1,0)=y;
    Targetstate(2,0)=phi;
}

void MYpainter::updateLeaderpos(double x, double y, double phi)
{
    Leaderstate(0,0)=x;
    Leaderstate(1,0)=y;
    Leaderstate(2,0)=phi;
}
