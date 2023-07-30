#include "managerkl.h"
#include "service/NonlinearSolverservice.h"
#include "Test_Use_HessionActivator.h"
#include "costtermas.h"
#include "iostream"
managerkl::managerkl()
{
    NonlinearSolverservice *m_service=Test_Use_HessionActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    simpleode *ode=new simpleode;
    simpleodejacob *odejac=new simpleodejacob;

    CostTermas *newset1=new CostTermas("optuna");
    std::shared_ptr<ifopt::ConstraintSet> consptr2(newset1);
    m_service->AddCostSet(consptr2);

    m_service->registerODE(ode);
    m_service->registerODEJacob(odejac);
    Eigen::MatrixXd initstate;initstate.resize(2,1);initstate.setConstant(3);
    Eigen::MatrixXd terminalstate;terminalstate=initstate;
    m_service->init_state(initstate,terminalstate);
    m_service->init_num(2,1,4);
    m_service->init_steptime(30*0.001);//此处时间单位为秒
    m_service->setuseterminal(false);
    m_service->Use_BuildIn_Dynamics_Cons(true);
    m_service->constructNLP();
    m_service->start_crack();

    Eigen::SparseMatrix<double, Eigen::RowMajor> Hes(2, 2);
    std::vector< Eigen::Triplet<double> > triplet_list;
    triplet_list.reserve(4);

    //    for (int k=0; k<2; ++k)
    //    {
    //        for (int i=0;i<2;++i)
    //        {
    //            triplet_list.push_back(Eigen::Triplet<double>(k, i,1));
    //        }
    //    }
    triplet_list.push_back(Eigen::Triplet<double>(1, 1,1));
    triplet_list.push_back(Eigen::Triplet<double>(1, 1,1));
    Hes.setFromTriplets(triplet_list.begin(), triplet_list.end());
    //复现了内容充分说明一点，之前报错就是因为triplest超了
    std::cout<<Hes<<std::endl;
}
