#include "planner_manager.h"
#include "swarm_path_planningActivator.h"
#include "obs_avoidence.h"
#include "collision_avoidence.h"
#include "xmlcore.h"
#include "minimize_topology.h"
#include "swarm_path_planningActivator.h"
#include "service/Datalogservice.h"
#include "topology_constrain.h"
#include "testconstrain.h"
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

    //    Obs_Avoidence *newset=new Obs_Avoidence(decnum*agentnum,"Obs_Avoidence");
    //    std::shared_ptr<ifopt::ConstraintSet> consptr(newset);
    //    m_service->AddConstraintSet(consptr);

    //        TestConstrain *newset=new TestConstrain(12);
    //        std::shared_ptr<ifopt::ConstraintSet> consptr(newset);
    //        m_service->AddConstraintSet(consptr);

    //    Collision_Avoidence *newset1=new Collision_Avoidence(decnum*agentnum*(agentnum-1)/2,"Collision_Avoidence");
    //    std::shared_ptr<ifopt::ConstraintSet> consptr1(newset1);
    //    m_service->AddConstraintSet(consptr1);


    minimize_Topology *newset2=new minimize_Topology("minimize_Topology");
    std::shared_ptr<ifopt::ConstraintSet> consptr2(newset2);
    m_service->AddCostSet(consptr2);

    //    swarmvehicle var_struct;
    //    common_initialize(var_struct);
    //    int op=0;
    //    for(int steps=0;steps<decnum;steps++)
    //    {
    //        for(int i=0;i<agentnum;i++)
    //        {
    //            int edge_num=(var_struct.steps[steps])->agents[i]->edgenum;
    //            for(int j=0;j<edge_num;j++)
    //            {
    //                  op+=1;
    //            }
    //        }
    //    }
    //    Topology_Constrain *newset3=new Topology_Constrain(op,"Topology_Constrain");
    //    std::shared_ptr<ifopt::ConstraintSet> consptr3(newset3);
    //    m_service->AddConstraintSet(consptr3);


    //一个想法是将最优化转化为约束问题
    //但是，我们需要搞明白这么干不会有用的机制
    //而不是频繁的更换，不知道底层原理是没有用的
    m_service->constructNLP();

    Eigen::MatrixXd input1;

    input1.resize(5*agentnum*decnum,1);
    input1.setOnes();//初始不能够这么设，会导致碰撞约束失效
    //setones会直接把变量设置到无变化率的位置上
    //所以不能这么干
    initilize_Variable(input1);//这一步会导致求解出问题！！就是这一步！！
    //！！为什么.....
    m_service->init_all_x(0,input1);
    //换一个初始值还真有用......
    //可是不能够一直这样吧，步数继续增长呢？

    m_service->solve_problem();
    Datalogservice *m_service=swarm_path_planningActivator::getService<Datalogservice>("Datalogservice");
    m_service->DeleteFile("./log/PATHPLAING/test.log");
    m_service->DeleteFile("./log/PATHPLAING/test.xls");
    m_service->createlogfile("./log/PATHPLAING/test.log",8946);
    newset2->GetCost();
    //    newset2->var_struct;
    QString word;

    m_service->createxlsfile("./log/PATHPLAING/test.xls");
    for(int k=0;k<newset2->decnum;k++)
    {
        for(int i=0;i<newset2->agentnum;i++)
        {
            word=" time : "+QString::number(k)+"agent "+
                   QString::number(i)+" status: " + QString::number(newset2->var_struct.steps[k]->agents[i]->x)
                   + " " + QString::number(newset2->var_struct.steps[k]->agents[i]->y) + " "
                   + QString::number(newset2->var_struct.steps[k]->agents[i]->phi);


            m_service->log(k,3*i+0,newset2->var_struct.steps[k]->agents[i]->x);
            m_service->log(k,3*i+1,newset2->var_struct.steps[k]->agents[i]->y);
            m_service->log(k,3*i+2,newset2->var_struct.steps[k]->agents[i]->phi);

        }
    }

    m_service->savexlsfile();
}
