#include "nonlinearplanner.h"
#include "xmlcore.h"
#include "swarm_path_planning_FeedBackActivator.h"
NonlinearPlanner::NonlinearPlanner()
{

    xmlCore xmlreader("./config/swarmmpc/swarm.xml");

    xmlreader.xmlRead("agent_num",agentnum);
    xmlreader.xmlRead("decnum",decnum);
    xmlreader.xmlRead("steptime",steptime);

    m_service=swarm_path_planning_FeedBackActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");

    m_ode=new Swarm_ODE;
    m_Jac= new Jacobiancalc;
    m_service->registerODE(m_ode);

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
    m_service->registerODEJacob(m_Jac);
    m_service->init_state(initstate,terminalstate);
    m_service->init_num(agentnum*3,agentnum*2,decnum);
    m_service->init_steptime(steptime*0.001);//此处时间单位为秒
    m_service->setuseterminal(false);
    m_service->Use_BuildIn_Dynamics_Cons(true);



    newset2=new minimize_Topology("minimize_Topology");
    std::shared_ptr<ifopt::ConstraintSet> consptr2(newset2);
    m_service->AddCostSet(consptr2);

    m_service->constructNLP();

    Eigen::MatrixXd input1;

    input1.resize(5*agentnum*decnum,1);input1.setZero();
    std::shared_ptr<Eigen::MatrixXd> initptr = std::make_shared<Eigen::MatrixXd>(input1);

    m_service->init_all_x(0,initptr);


}

void NonlinearPlanner::plan(Eigen::MatrixXd &statesOfall, Eigen::MatrixXd &Target, Eigen::MatrixXd &planed)
{
    //在这里执行规划任务
    Eigen::MatrixXd input1;

    input1.resize(agentnum*3,1);input1.setZero();
    for(int i=0;i<agentnum;i++)
    {
        input1(3*i+0,0)=statesOfall(i,0);
        input1(3*i+1,0)=statesOfall(i,1);
        input1(3*i+2,0)=statesOfall(i,2);
    }
    //现在麻烦的事情就是，无法求解....
    m_service->ReinitState(input1,input1);


    //这里初始化所有的变量
    Eigen::MatrixXd input2;
    input2.resize(5*agentnum*decnum,1);input2.setZero();

    for(int i=0;i<decnum;i++)
    {
        for(int j=0;j<agentnum;j++)
        {
            input2(2+5*agentnum*i+j*5+0,0)=Target(i,0);
            input2(2+5*agentnum*i+j*5+1,0)=Target(i,1);
            input2(2+5*agentnum*i+j*5+2,0)=Target(i,2);
        }
//        newset2->copymatvalue(Target(i,0),Target(i,1),i);
    }
    std::shared_ptr<Eigen::MatrixXd> initptr = std::make_shared<Eigen::MatrixXd>(input2);

    m_service->init_all_x(0,initptr);

    //最后，求解
    m_service->start_crack();
    //编码矩阵
//    newset2->GetCost();

//    for(int k=0;k<newset2->decnum;k++)
//    {
//        for(int i=0;i<newset2->agentnum;i++)
//        {
//            planed(k,i*5+0)=newset2->var_struct.steps[k]->agents[i]->x;
//            planed(k,i*5+1)=newset2->var_struct.steps[k]->agents[i]->y;
//            planed(k,i*5+2)=newset2->var_struct.steps[k]->agents[i]->phi;
//            planed(k,i*5+3)=newset2->var_struct.steps[k]->agents[i]->v;
//            planed(k,i*5+4)=newset2->var_struct.steps[k]->agents[i]->w;

//        }
//    }

}
