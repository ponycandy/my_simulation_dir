#include "simmanager.h"
#include "service/SwarmSimservice.h"
#include "swarm_NLPSimulatorActivator.h"
#include "OSGIEVENT.h"
#include "service/SwarmSimservice.h"
#include "service/Datalogservice.h"
#include "service/TCPserverservice.h"
simmanager::simmanager(QObject *parent)
    : QObject{parent}
{
    intercounts=0;
    QString filename="./config/DistributedMPC/swarm.xml";
    m_painter=new MYpainter;
    singleone=new vehicle;
    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    SwarmSimservice *swarmsim0=swarm_NLPSimulatorActivator::getService<SwarmSimservice>("SwarmSimservice");
    SwarmSimservice *swarmsim=swarmsim0->cloneservice();
    Datalogservice *logger=swarm_NLPSimulatorActivator::getService<Datalogservice>("Datalogservice");

    swarmsim->init_plant(30,filename,singleone);
    agentgroup=swarmsim->getagentgroup();
    Eigen::MatrixXd relationmatrix;
    relationmatrix.resize(agentnum,agentnum);

    TCPserverservice *m_server=swarm_NLPSimulatorActivator::getService<TCPserverservice>("TCPserverservice");
    xmlreader.xmlRead("relationmatrix",relationmatrix);

    vehicle *agent=dynamic_cast<vehicle *>( agentgroup[agentnum]);
    agent->logger=logger->cloneservice();
    agent->logger->createlogfile("./log/ETM_Target.txt",6056);
    agent->logger->DeleteFile("./log/ETM_Target.xls");
    agent->logger->createxlsfile("./log/ETM_Target.xls");

    for(int i=1;i<=agentnum-1;i++)
    {
        vehicle *agent=dynamic_cast<vehicle *>( agentgroup[i]);



        QObject::connect(agent,SIGNAL(sigNLPback()),this,SLOT(returncount()),Qt::DirectConnection);

        agent->logger=logger->cloneservice();
        QString filename="./log/ETM_Agent_"+QString::number(i)+".xls";

        agent->logger->createlogfile("./log/ETM_Agent_"+QString::number(i)+".txt",6056+i);
        agent->logger->DeleteFile(filename);
        agent->logger->createxlsfile(filename);

        int portnum=8450+i;

        agent->m_decode->Server_mode_connect(portnum);
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
    m_start=new startwindow;
    m_start->show();
    QObject::connect(m_start,SIGNAL(sigstart()),this,SLOT(slotstart()),Qt::QueuedConnection);
    dysim->set_step_in_mode(1);
    intercounts=0;
}

void simmanager::slotstart()
{
//    m_start->hide();
    while(true)
    {

        dysim->step_in_control();
        while(true)
        {
            if(intercounts==agentnum-1)//最后一个agent是ref轨迹
            {
                intercounts=0;
                break;//控制变量就位，可以执行下一步ODE了

            }
            else
            {
                QElapsedTimer et;
                et.start();

                while(et.elapsed()<1)//ms
                {
                    QCoreApplication::processEvents();
                }
            }
        }
        for(int i=1;i<=agentnum;i++)
        {
            vehicle *agent=dynamic_cast<vehicle *>( agentgroup[i]);
            agent->implementcontrol();
        }
        dysim->step_in_ode();
        dysim->step_in_sensor();
        dysim->step_in_broadcast();

        //各车自行解决和本车控制器的通讯

    }
}

void simmanager::returncount()
{
    intercounts++;
}

