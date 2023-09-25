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
//    m_service->AddCostSet(consptr2);

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
    input1.setZero();//初始不能够这么设，会导致碰撞约束失效

    //setones会直接把变量设置到无变化率的位置上
    //所以不能这么干
    initilize_Variable(input1,initstate);//这一步会导致求解出问题！！就是这一步！！
    input1=input1*1.2;
    //卧槽，问题还是在init_all_x里面，必须使用eval方法复制内存！，然后就OK了？
    //！！为什么.....
    //已经证明，重新编译或者本机编译无法解决这个问题，也就是说不是编译的问题！
    std::shared_ptr<Eigen::MatrixXd> initptr = std::make_shared<Eigen::MatrixXd>(input1);
    //最后尝试，所有相关值都通过指针传入
    m_service->init_all_x(0,initptr);
    //也不会是init_all_x造成的问题，因为这一步对于其它的初始值是OK的
    //所以唯一的问题就是初始的具体值
    //换一个初始值还真有用......
    //可是不能够一直这样吧，步数继续增长呢？

    //ipopt的所有输入和输出都必须用smartponter，还不能是普通指针
    //根据github上的作者页，这个bug可能会延伸到ifopt的所有相关依赖上面
    //这就是为什么，当我们把矩阵的初始值赋值从等号改为eval就好了
    //注意，只要没有restoration的前提下发生了崩溃
    //那就一定不是因为问题本身性质导致的
    //而是因为API的指针释放导致的

    //惊了，求解器的问题，mumps和ma57都不行，但是ma27可以完美求解，不会报错
    m_service->solve_problem();

//    Datalogservice *m_service=swarm_path_planningActivator::getService<Datalogservice>("Datalogservice");
//    m_service->DeleteFile("./log/PATHPLAING/test.log");
//    m_service->DeleteFile("./log/PATHPLAING/test.xls");
//    m_service->createlogfile("./log/PATHPLAING/test.log",8946);
//    newset2->GetCost();
//    //    newset2->var_struct;
//    QString word;

//    m_service->createxlsfile("./log/PATHPLAING/test.xls");
//    for(int k=0;k<newset2->decnum;k++)
//    {
//        for(int i=0;i<newset2->agentnum;i++)
//        {
//            word=" time : "+QString::number(k)+"agent "+
//                   QString::number(i)+" status: " + QString::number(newset2->var_struct.steps[k]->agents[i]->x)
//                   + " " + QString::number(newset2->var_struct.steps[k]->agents[i]->y) + " "
//                   + QString::number(newset2->var_struct.steps[k]->agents[i]->phi);


//            m_service->log(k,3*i+0,newset2->var_struct.steps[k]->agents[i]->x);
//            m_service->log(k,3*i+1,newset2->var_struct.steps[k]->agents[i]->y);
//            m_service->log(k,3*i+2,newset2->var_struct.steps[k]->agents[i]->phi);

//        }
//    }

//    m_service->savexlsfile();
}
