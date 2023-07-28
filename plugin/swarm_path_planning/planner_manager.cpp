#include "planner_manager.h"
#include "swarm_path_planningActivator.h"
#include "obs_avoidence.h"
#include "collision_avoidence.h"
#include "xmlcore.h"
#include "minimize_topology.h"
planner_manager::planner_manager(QObject *parent)
    : QObject{parent}
{
    int agentnum;
    int steptime;
    int decnum;
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");

    xmlreader.xmlRead("agent_num",agentnum);
    xmlreader.xmlRead("decnum",decnum);
    xmlreader.xmlRead("steptime",steptime);

    //输入变量还是选择原始变量而不是误差变量，这样方便对碰撞进行操作
    m_service=swarm_path_planningActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    //    m_service->set_control_bound(lowb,highb);
    m_ode=new Swarm_ODE;
    m_Jac= new Jacobiancalc;
    m_service->registerODE(m_ode);
    //这里是误差模型

    Eigen::MatrixXd agent_mat;
    agent_mat.resize(agentnum,3);
    xmlreader.xmlRead("agent_mat",agent_mat);

    Eigen::MatrixXd initstate;
    initstate.resize(3*agentnum,1);
    int m=0;
    for (int i = 0; i < agent_mat.rows(); ++i)
    {
        for (int j = 0; j < agent_mat.cols(); ++j)
        {
            initstate(m)=agent_mat(i, j);
            m++;
        }
    }
    Eigen::MatrixXd terminalstate=initstate;
    //展平agentmat作为initstate的值
    m_service->registerODEJacob(m_Jac);
    m_service->init_state(initstate,terminalstate);
    m_service->init_num(agentnum*3,agentnum*2,decnum);
    m_service->init_steptime(steptime*0.001);//此处时间单位为秒
    m_service->setuseterminal(false);
    m_service->Use_BuildIn_Dynamics_Cons(true);
//    Obs_Avoidence *newset=new Obs_Avoidence(agentnum,"Obs_Avoidence");
//    std::shared_ptr<ifopt::ConstraintSet> consptr(newset);
//    m_service->AddConstraintSet(consptr);
    //这里不能够用最大化约束，因为Ipopt会给拉到无限远，这是一个无限势墙。算法本质导致的！
    Collision_Avoidence *newset1=new Collision_Avoidence(decnum*agentnum*(agentnum-1)/2,"Collision_Avoidence");
    std::shared_ptr<ifopt::ConstraintSet> consptr1(newset1);
    m_service->AddConstraintSet(consptr1);


//    minimize_Topology *newset2=new minimize_Topology("minimize_Topology");
//    std::shared_ptr<ifopt::ConstraintSet> consptr2(newset2);
//    m_service->AddCostSet(consptr2);
    //    m_service->AddVariableSet(std::make_shared<Variable_new>());
    m_service->constructNLP();

    m_service->solve_problem();
}
