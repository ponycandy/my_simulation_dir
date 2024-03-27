#include "simmanager.h"
#include "xmlcore.h"
#include "Vehicle_Swarm_UWB_simulatorActivator.h"
#include "OSGIEVENT.h"
simmanager::simmanager(QObject *parent)
    : QObject{parent}
{
    intercounts=0;
    // QString filename="./config/DistributedMPC/swarmUWB.xml";
    QString filename="D:/QT/prjdir/OSGIMODULE/my_simulation_dir/build/config/DistributedMPC/swarmUWB.xml";
    m_painter=new MYpainter;
    singleone=new vehicle;

    QObject::connect(this,SIGNAL(update_target(double, double)),singleone,
                SLOT(slot_update_target(double , double )),Qt::QueuedConnection);


    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    SwarmSimservice *swarmsim0=Vehicle_Swarm_UWB_simulatorActivator::getService<SwarmSimservice>("SwarmSimservice");
    SwarmSimservice *swarmsim=swarmsim0->cloneservice();
    Datalogservice *logger=Vehicle_Swarm_UWB_simulatorActivator::getService<Datalogservice>("Datalogservice");

    swarmsim->init_plant(30,filename,singleone);
    agentgroup=swarmsim->getagentgroup();
    Eigen::MatrixXd relationmatrix;
    relationmatrix.resize(agentnum,agentnum);

    xmlreader.xmlRead("relationmatrix",relationmatrix);

    vehicle *agent=dynamic_cast<vehicle *>( agentgroup[agentnum]);

    agent->logger=logger->cloneservice();
    agent->logger->createlogfile("./log/ETM_Target.txt",6056);
    agent->logger->DeleteFile("./log/ETM_Target.xls");
    agent->logger->createxlsfile("./log/ETM_Target.xls");
    m_start=new startwindow;
    m_start->show();
    for(int i=1;i<=agentnum;i++)
    {
        vehicle *agent=dynamic_cast<vehicle *>( agentgroup[i]);


        // QObject::connect(agent,SIGNAL(sigNLPback()),this,SLOT(returncount()),Qt::DirectConnection);

        QObject::connect(m_start,SIGNAL(sigstop()),agent,SLOT(Onstop()),Qt::QueuedConnection);
        QObject::connect(m_start,SIGNAL(sigspin()),agent,SLOT(Onspin()),Qt::QueuedConnection);

        // Vehicle_Swarm_UWB_simulatorActivator::subscribeslot(agent,SLOT(Onstop()),OSGIEVENT::SIG_SWARMSIMULATOR_SIGSTOP,Qt::QueuedConnection);
        // Vehicle_Swarm_UWB_simulatorActivator::subscribeslot(agent,SLOT(Onspin()),OSGIEVENT::SIG_SWARMSIMULATOR_SIGSPIN,Qt::QueuedConnection);


        agent->logger=logger->cloneservice();
        QString filename="./log/ETM_Agent_"+QString::number(i)+".xls";

        agent->logger->createlogfile("./log/ETM_Agent_"+QString::number(i)+".txt",6056+i);
        agent->logger->DeleteFile(filename);
        agent->logger->createxlsfile(filename);

        int portnum=8450+i;

        // agent->m_decode->Server_mode_connect(portnum);
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
    // m_widget->resize(1200,800);
    // m_widget->show();

    m_start->setParent(m_widget);
    m_start->move(0,0);
    anim->start_animate();
    dysim=swarmsim->get_simer();



    dysim->set_step_in_mode(0);
    intercounts=0;

    Vehicle_Swarm_UWB_simulatorActivator::subscribeslot(this,SLOT(slot_mouse_pressed(double,double,double,double))
                                     ,OSGIEVENT::MOUSE_PRESSED,Qt::QueuedConnection);
    qDebug()<<"UWB_controller初始化完成";

    Vehicle_Swarm_UWB_simulatorActivator::subscribeslot(this,SLOT(slot_choose_bool(bool)),OSGIEVENT::SIG_SWARMSIMULATOR_SIGCHOOSE,Qt::QueuedConnection);

    QObject::connect(m_start,SIGNAL(sigstart()),this,
                     SLOT(dysimslotstart()),Qt::QueuedConnection);

    QObject::connect(m_start,SIGNAL(sig_choose_bool(bool)),this,
                     SLOT(slot_choose_bool(bool)),Qt::QueuedConnection);

    QObject::connect(this,SIGNAL(update_target(double, double)),singleone,
                     SLOT(slot_update_target(double , double )),Qt::QueuedConnection);


}
void simmanager::dysimslotstart()
{
    dysim->start_sim();//多线程运行
}

void simmanager::slot_choose_bool(bool choosenow)
{
    choosenow_flag=choosenow;
}

void simmanager::slot_mouse_pressed(double x, double y, double pix_x, double pix_y)
{
    if(true)
    {
        qDebug()<<x<<" "<<y;
        emit update_target(x, y);
    }
    else
    {

    }
}

