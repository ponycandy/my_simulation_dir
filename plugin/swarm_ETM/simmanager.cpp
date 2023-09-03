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
    QString filename="./config/swarmETM/swarm.xml";
    singleone=new vehicle;
    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    SwarmSimservice *swarmsim0=swarm_ETMActivator::getService<SwarmSimservice>("SwarmSimservice");
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
            agent->logger=logger->cloneservice();
            agent->logger->createlogfile("./log/ETM_Target.txt",6056);
            agent->logger->createxlsfile("./log/ETM_Target.xls");
            agent->setsendsig(0);//设置目标发送信号
            agent->status_num=3;
            Eigen::MatrixXd mid1;
            mid1.resize(3,1);
            mid1=agent->state_vector.block(0,0,3,1);
            agent->state_vector.resize(3,1);
            agent->state_vector=mid1;
        }

        else
        {
            agent->logger=logger->cloneservice();
            QString filename="./log/ETM_Agent_"+QString::number(i)+".xls";

            agent->logger->createlogfile("./log/ETM_Agent_"+QString::number(i)+".txt",6056+i);
            agent->logger->createxlsfile(filename);

            agent->setsendsig(1);//设置接受信号
        }
        for(int k=0;k<agentnum;k++)
        {
            if(relationmatrix(i-1,k)!=0)
            {
                agent->nearbyagentdistance.insert(k+1,relationmatrix(i-1,k));
            }
        }


    }
    MYpainter *m_painter=new MYpainter;
    Animateservice *anim=swarmsim->getwidgetoperator();
    anim->register_painter(m_painter);
    QWidget *m_widget=anim->getwidget();
    m_widget->resize(1200,800);
    m_widget->show();
    anim->start_animate();
    dysim=swarmsim->get_simer();
    swarmsim->startsim();

}

void simmanager::on_trigger()
{
    QMap<int, SwarmAgent *>::const_iterator iter2 = agentgroup.cbegin();
    while (iter2 != agentgroup.cend())
    {
        iter2.value()->TriggerEvent();
        ++iter2;
    }
}
