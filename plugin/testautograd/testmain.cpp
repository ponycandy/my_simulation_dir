#include "testmain.h"
#include "testautogradActivator.h"
#include "variablexl.h"
#include "costfunc.h"
#include "iostream"
Testmain::Testmain(QObject *parent)
    : QObject{parent}
{
    m_service= testautogradActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    variablexl *VAR;
    VAR=new variablexl(5);
    std::shared_ptr<ifopt::VariableSet> VARptr(VAR);
    m_service->AddVariableSet(VARptr);

    costfunc *tcost;
    tcost=new costfunc;
    std::shared_ptr<ifopt::ConstraintSet> Dtcostptr(tcost);
    m_service->AddCostSet(Dtcostptr);

    m_service->start_crack();
    double v=tcost->GetCost();
    qDebug()<<v;
}
