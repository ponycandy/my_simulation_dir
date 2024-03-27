#include "simulator_manager.h"
#include "SwarmSimulatorActivator.h"
#include "algorithm"
#include "xmlcore.h"
simulator_manager::simulator_manager(QObject *parent) : QObject(parent)
{
    Animateservice *Anim_service_0=SwarmSimulatorActivator::getService<Animateservice>("Animateservice");
    SimDynamicsservice *SimDy_service_0=SwarmSimulatorActivator::getService<SimDynamicsservice>("SimDynamicsservice");
    Colli_service=SwarmSimulatorActivator::getService<CollisionDetectservice>("CollisionDetectservice");
    Anim_service=Anim_service_0;
    SimDy_service=SimDy_service_0->cloneservice();
    thread_ID=0;
    neibseq=0;
    paint=new MYpainter;
    Anim_service->register_painter(paint);
    m_sim=new Simulator;

    qRegisterMetaType<QMap<int,SwarmAgent*>>("QMap<int,SwarmAgent*>");
    connect(m_sim,SIGNAL(sig_agent_state_update(QMap<int,SwarmAgent*>)),paint,SLOT(slot_update_state(QMap<int,SwarmAgent*>)),Qt::QueuedConnection);


    qRegisterMetaType<QMap<int,SwarmObstacle*> >("QMap<int,SwarmObstacle*>");
    connect(m_sim,SIGNAL(sig_obs_state_update(QMap<int,SwarmObstacle*>)),paint,SLOT(slot_obs_state_update(QMap<int,SwarmObstacle*>)),Qt::QueuedConnection);
    m_sim->init(thread_ID);
    connect(this,SIGNAL(startsimnow()),this,SLOT(slotstartsim()),Qt::QueuedConnection);
}

Animateservice *simulator_manager::getwidgetoperator()
{
    return Anim_service;
}

SwarmSimservice *simulator_manager::cloneservice()
{
    simulator_manager* new_service=new simulator_manager;
    new_service->thread_ID=thread_ID+1;
    new_service->m_sim->init(new_service->thread_ID);
    return new_service;
}

SimDynamicsservice *simulator_manager::get_simer()
{
    return SimDy_service;
}

QMap<int, SwarmAgent *> simulator_manager::getagentgroup()
{
    return m_sim->Agents_group;
}

void simulator_manager::startsim()
{

    SimDy_service->start_sim();
    //    SimDy_service->start_sim();
}
void simulator_manager::haultsim()
{
    SimDy_service->stop_sim();
}
void simulator_manager::init_plant(int steptime, QString configfile, SwarmAgent *singleagents)
{
    //需要更改，从外部选择配置文件！
    int states_num=0;
    xmlCore xmlreader(configfile.toStdString());

    xmlreader.xmlRead("agent_num",m_sim->agent_num);
    xmlreader.xmlRead("states_num",states_num);

    xmlreader.xmlRead("obs_num",m_sim->obs_num);
    xmlreader.xmlRead("steptime",m_sim->delta_t);

    Eigen::MatrixXd agent_mat;
    agent_mat.resize(m_sim->agent_num,states_num);
    xmlreader.xmlRead("agent_mat",agent_mat);

    SimDy_service->set_delta_t(m_sim->delta_t);
    SimDy_service->set_ODE(m_sim);

    Eigen::MatrixXd obs_mat;
    for(int i=1;i<=m_sim->obs_num;i++)
    {
        SwarmObstacle *new_obs=new SwarmObstacle;
        QString obs_term_name="OBS_"+QString::number(i)+"_vertexnum";
        xmlreader.xmlRead(obs_term_name.toStdString(),new_obs->vertex_num);
        new_obs->ID=i;
        obs_mat.resize(new_obs->vertex_num,2);
        obs_term_name="OBS_"+QString::number(i)+"_vertexparams";
        std::vector<double> point_x_vec;
        std::vector<double> point_y_vec;
        xmlreader.xmlRead(obs_term_name.toStdString(),obs_mat);
        for(int j=1;j<=new_obs->vertex_num;j=j+1)
        {
            double x= obs_mat(j-1,0);
            double y= obs_mat(j-1,1);
            point_x_vec.push_back(x);
            point_y_vec.push_back(y);
            new_obs->vertex_map<<QPointF(x,y);
        }

        double max_x = *max_element(point_x_vec.begin(), point_x_vec.end());
        double max_y = *max_element(point_y_vec.begin(), point_y_vec.end());
        double min_x = *min_element(point_x_vec.begin(), point_x_vec.end());
        double min_y = *min_element(point_y_vec.begin(), point_y_vec.end());

        xmlreader.xmlRead("communication_range",singleagents->communication_range);
        xmlreader.xmlRead("collision_r",singleagents->collision_r);

        new_obs->x_up=max_x+singleagents->collision_r;
        new_obs->x_low=min_x-singleagents->collision_r;
        new_obs->y_up=max_y+singleagents->collision_r;
        new_obs->y_low=min_y-singleagents->collision_r;

        m_sim->obsbounding_group.insert(i,new_obs);
    }

    for(int i=1;i<=m_sim->agent_num;i++)
    {
        SwarmAgent *new_agent=singleagents->clone_agent();
        new_agent->state_vector.resize(states_num,1);
        new_agent->ID=i;
        for(int j=0;j<new_agent->status_num;j++)
        {
            new_agent->state_vector(j,0)=agent_mat(i-1,j);
            new_agent->act_vector.resize(new_agent->action_num,1);
            new_agent->act_vector.setZero();
            xmlreader.xmlRead("communication_range",new_agent->communication_range);
            xmlreader.xmlRead("collision_r",new_agent->collision_r);

        }
        m_sim->Agents_group.insert(i,new_agent);
    }
    m_sim->state_array.resize(m_sim->agent_num,states_num);
    m_sim->act_array.resize(m_sim->agent_num,singleagents->action_num);
    m_sim->act_array.setZero();
    m_sim->state_array.setZero();
    m_sim->update_obs();
    m_sim->agent_communication_range=m_sim->Agents_group.value(1)->communication_range;
    xmlreader.xmlRead("collision_r",m_sim->collision_r);
    //确立ETM机制,下面的机制默认是将全局的相对状态储存
    //所以，实际上需要算法自行管理邻居！
    //我们还想要考虑吧一个selfETM更新，只有邻居能够收到的场景....
    for(int i=1;i<=m_sim->agent_num;i++)
    {
        SwarmAgent *agent=m_sim->Agents_group.value(i);
        agent->ETM_vec.resize(m_sim->agent_num+1);
        agent->ETM_sensor.resize(m_sim->agent_num+1);
        agent->ETM_Flag.resize(m_sim->agent_num+1);

        for(int j=1;j<=m_sim->agent_num;j++)
        {
            agent->ETM_vec[j]=&m_sim->Agents_group.value(j)->selfETM;
            agent->ETM_sensor[j]=new Eigen::MatrixXd;//这里无法赋值
            agent->ETM_Flag[j]=1;//设置被触发
            *(agent->ETM_sensor[j])=(( agent->ETM_vec[j]))->eval();
            // agent->ETM_sensor[j]=( agent->ETM_vec[j])->eval();

        }

    }



}

void simulator_manager::set_neib_sequnce(int flag)
{
    neibseq=1;
    m_sim->neib_seq=1;
}

void simulator_manager::slotstartsim()
{
    SimDy_service->start_sim();

}
