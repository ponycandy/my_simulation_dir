#include "testmain.h"
#include "testautogradActivator.h"
#include "variablexl.h"
#include "costfunc.h"
#include "iostream"
#include "constraintest.h"
Testmain::Testmain(QObject *parent)
    : QObject{parent}
{
    m_service= testautogradActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    variablexl *VAR;
    Eigen::MatrixXd varmat;
    varmat.resize(5,1);
    varmat<<0.840899,1.18921,0.840899,0,0;
    VAR=new variablexl(5);
    VAR->data=varmat;
    std::shared_ptr<ifopt::VariableSet> VARptr(VAR);
    m_service->AddVariableSet(VARptr);

    costfunc *tcost;
    tcost=new costfunc;
    std::shared_ptr<ifopt::ConstraintSet> Dtcostptr(tcost);
    m_service->AddCostSet(Dtcostptr);

    constraintest *cstest;
    cstest=new constraintest(2,"asd");
    std::shared_ptr<ifopt::ConstraintSet> Dtcostptr1(cstest);
    m_service->AddConstraintSet(Dtcostptr1);
    varmat.setRandom();
//    m_service->init_all_x(0,varmat);//这个只有使用内在动力学的时候才能够使用
    m_service->start_crack();
    double v=tcost->GetCost();
//    qDebug()<<"value is "<<v;
    std::cout<<VAR->GetValues()<<std::endl;

}
