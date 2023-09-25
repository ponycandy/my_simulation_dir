#include "simmanager.h"
#include "service/SwarmSimservice.h"
#include "swarm_path_planning_FeedBackActivator.h"
#include "OSGIEVENT.h"
#include "service/SwarmSimservice.h"
#include "service/Datalogservice.h"
simmanager::simmanager(QObject *parent)
    : QObject{parent}
{
    QString filename="./config/swarmmpc/swarm.xml";
    m_painter=new MYpainter;
    singleone=new vehicle;
    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    SwarmSimservice *swarmsim0=swarm_path_planning_FeedBackActivator::getService<SwarmSimservice>("SwarmSimservice");
    SwarmSimservice *swarmsim=swarmsim0->cloneservice();
    swarmsim->init_plant(30,filename,singleone);
    agentgroup=swarmsim->getagentgroup();
    Eigen::MatrixXd relationmatrix;
    relationmatrix.resize(agentnum,agentnum);


    xmlreader.xmlRead("relationmatrix",relationmatrix);

    for(int i=1;i<=agentnum;i++)
    {
        vehicle *agent=dynamic_cast<vehicle *>( agentgroup[i]);

        agent->agentnum=agentnum;

        if(i==agentnum)
        {
            agent->m_planner=new NonlinearPlanner;
            agent->setsendsig(0);//设置目标接受信号
            agent->InternalState=agent->state_vector.eval();
        }

        else
        {
            agent->setsendsig(1);//设置发送信号
        }
        for(int k=0;k<agentnum;k++)
        {
            if(relationmatrix(i-1,k)!=0)
            {
                agent->nearbyagentdistance.insert(k+1,relationmatrix(i-1,k));
            }
        }


    }
    Animateservice *anim=swarmsim->getwidgetoperator();
    QWidget *m_widget=anim->getwidget();
    anim->register_painter(m_painter);
    m_widget->resize(1200,800);
    m_widget->show();
    anim->start_animate();
    dysim=swarmsim->get_simer();
    swarmsim->startsim();

}

