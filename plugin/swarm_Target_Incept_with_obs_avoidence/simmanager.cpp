#include "simmanager.h"
#include "service/SwarmSimservice.h"
#include "swarm_Target_Incept_with_obs_avoidenceActivator.h"
#include "OSGIEVENT.h"
#include "service/SwarmSimservice.h"

simmanager::simmanager(QObject *parent)
    : QObject{parent}
{

    m_painter=new MYpainter;
    QString filename="./config/swarmInception/swarm.xml";
    singleone=new vehicle;
    xmlCore xmlreader(filename.toStdString());
    xmlreader.xmlRead("agent_num",agentnum);
    SwarmSimservice *swarmsim0=swarm_Target_Incept_with_obs_avoidenceActivator::getService<SwarmSimservice>("SwarmSimservice");
    SwarmSimservice *swarmsim=swarmsim0->cloneservice();
    swarmsim->init_plant(30,filename,singleone);
    agentgroup=swarmsim->getagentgroup();
    Eigen::MatrixXd relationmatrix;
    int edgenum;
    int vertexnum;
    xmlreader.xmlRead("Edge_num",edgenum);
    xmlreader.xmlRead("Vertex_num",vertexnum);
    relationmatrix.resize(vertexnum,vertexnum);
    xmlreader.xmlRead("relationmatrix",relationmatrix);
    for(int i=1;i<=agentnum;i++)
    {
        vehicle *agent=dynamic_cast<vehicle *>( agentgroup[i]);
        Datalogservice *m_sss=swarm_Target_Incept_with_obs_avoidenceActivator::getService<Datalogservice>("Datalogservice");
        agent->M_logger=m_sss->cloneservice();

        //需要每个agent按照其自身对应的ID采取不同的措施
        //此处设置1号为领导者
        if(i==agentnum)
        {
            agent->setsendsig(0);//设置目标发送信号
            agent->status_num=3;
            Eigen::MatrixXd mid1;
            mid1.resize(3,1);
            mid1=agent->state_vector.block(0,0,3,1);
            agent->state_vector.resize(3,1);
            agent->state_vector=mid1;
        }
        if(i==1)
        {
            agent->setsendsig(1);//设置领导发送信号
            //领导的感知/通讯范围要远大于其它无人车
            //每辆无人车具备有限的感知能力
            agent->communication_range=100;
            agent->sensor_range=100;
            for(int k=0;k<vertexnum;k++)
            {
                if(relationmatrix(i-1,k)!=0)
                {
                    agent->nearbyagentdistance.insert(k+1,relationmatrix(i-1,k));
                }
            }
//            agent->collision_r=10; //这个还是不要改变，否则会导致避障行为发生很大的变化
        }
        if(i<agentnum && i>1)
        {
            agent->setsendsig(2);//设置follower信号
            for(int k=0;k<vertexnum;k++)
            {
                if(relationmatrix(i-1,k)!=0)
                {
                    agent->nearbyagentdistance.insert(k+1,relationmatrix(i-1,k));
                }
            }
        }
    }
    Animateservice *anim=swarmsim->getwidgetoperator();
    anim->register_painter(m_painter);
    //这个painter用来额外画出目标agent的位置，也就是红色标绿
    QWidget *m_widget=anim->getwidget();
    m_widget->resize(1200,800);
    m_widget->show();
    anim->start_animate();
    dysim=swarmsim->get_simer();
    swarmsim->startsim();
}
