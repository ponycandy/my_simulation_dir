#include "simmanager.h"
#include "service/SwarmSimservice.h"
#include "Swarm_obstacle_avoidActivator.h"
#include "OSGIEVENT.h"
#include "service/SwarmSimservice.h"

simmanager::simmanager(QObject *parent)
    : QObject{parent}
{
      auto my_logger = spdlog::basic_logger_mt("file_logger", "logs/testswarm.txt", true);

//    TCPsoc=Swarm_obstacle_avoidActivator::getService<Tcpcommunicateservice>("Tcpcommunicateservice");
//    Swarm_obstacle_avoidActivator::subscribeslot(this,SLOT(matrecieved(Eigen::MatrixXd))
//                                                ,OSGIEVENT::MAT_GET_NOW,Qt::QueuedConnection);
//    //    Animateservice *Anim_service=swarm_rl_experimentActivator::getService<Animateservice>("Animateservice");
//    TCPsoc->setport("8001","127.0.0.1");
//    TCPsoc->connectport();
//    decoder=Swarm_obstacle_avoidActivator::getService<CPYcoderservice>("CPYcoderservice");


      m_painter=new MYpainter;
    QString filename="./config/swarm/swarm.xml";
    singleone=new vehicle;
    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    SwarmSimservice *swarmsim0=Swarm_obstacle_avoidActivator::getService<SwarmSimservice>("SwarmSimservice");
    SwarmSimservice *swarmsim=swarmsim0->cloneservice();
    swarmsim->init_plant(30,filename,singleone);
    agentgroup=swarmsim->getagentgroup();
    for(int i=1;i<agentnum;i++)
    {
        vehicle *agent=dynamic_cast<vehicle *>( agentgroup[i]);
        agent->my_logger=my_logger;
    }
    Animateservice *anim=swarmsim->getwidgetoperator();
    anim->register_painter(m_painter);
    QWidget *m_widget=anim->getwidget();
    m_widget->resize(1200,800);
    m_widget->show();
    anim->start_animate();
    dysim=swarmsim->get_simer();
//    dysim->set_step_in_mode(1);
    swarmsim->startsim();
}
void simmanager::matrecieved(Eigen::MatrixXd mat)
{
    //输入数据所有机器人的一次性控制量，维度重新计算
    if(mat.rows()==agentnum && mat.cols()==2)//控制指令
    {
        QMap<int, SwarmAgent *>::const_iterator iter = agentgroup.cbegin();
        int i=0;
        while (iter != agentgroup.cend())
        {
            iter.value()->act_vector(0,0)=mat(i,0);
            iter.value()->act_vector(1,0)=mat(i,1);
            ++iter;
            i++;
        }

        dysim->step_in();
        //返回数据不好决定
        Eigen::MatrixXd matreturn;

        matreturn.resize(4,9);
        matreturn.setZero();

        iter = agentgroup.cbegin();
        for (int i=0;i<=agentnum;i++)
        {
            matreturn(0,3*i)=iter.value()->state_vector(0,0);
            matreturn(0,3*i+1)=iter.value()->state_vector(1,0);
            matreturn(0,3*i+2)=iter.value()->state_vector(2,0);
            iter++;
        }
        //所有的状态变量存在第一行

//        decoder->sendMAT(matreturn,TCPsoc);//返回3*9矩阵
        //then send mat
    }


    if(mat.rows()==1 && mat.cols()==1)//重置指令
    {
    }

}
