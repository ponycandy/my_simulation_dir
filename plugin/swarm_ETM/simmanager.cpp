#include "simmanager.h"
#include "service/SwarmSimservice.h"
#include "swarm_ETMActivator.h"
#include "OSGIEVENT.h"
#include "service/SwarmSimservice.h"
#include "mypainter.h"
#include "service/Datalogservice.h"
simmanager::simmanager(QObject *parent)
    : QObject{parent}
{
    Datalogservice *logger=swarm_ETMActivator::getService<Datalogservice>("Datalogservice");
    QString filename="./config/swarmETM/swarm0.xml";
    singleone=new vehicle;
    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    SwarmSimservice *swarmsim0=swarm_ETMActivator::getService<SwarmSimservice>("SwarmSimservice");
    SwarmSimservice *swarmsim=swarmsim0->cloneservice();
    swarmsim->init_plant(30,filename,singleone);
    agentgroup=swarmsim->getagentgroup();



    for(int i=1;i<=agentnum;i++)
    {
        vehicle *agent=dynamic_cast<vehicle *>( agentgroup[i]);
        agent->fault_set(0);
    }
    MYpainter *m_painter=new MYpainter;
    Animateservice *anim=swarmsim->getwidgetoperator();
    anim->register_painter(m_painter);
    QWidget *m_widget=anim->getwidget();
    m_widget->resize(1200,800);
    m_widget->show();
    anim->start_animate();
    dysim=swarmsim->get_simer();
    //需要一个开始按钮
    mainwindow = new TestTriggered();
    connect(mainwindow,SIGNAL(trigeronce()),this,SLOT(on_trigger()));
    mainwindow->show();
}

void simmanager::on_trigger()
{
    for(int i=1;i<=agentnum;i++)
    {
        vehicle *agent=dynamic_cast<vehicle *>( agentgroup[i]);
        agent->predicitTraj();
    }
    dysim->start_sim();
}
