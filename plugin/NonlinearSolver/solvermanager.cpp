#include "solvermanager.h"
#include "NonlinearSolverActivator.h"
#include "service/NonlinearSolverservice.h"
solverManager::solverManager(QObject *parent)
    : QObject{parent}
{
    m_problem=new ProblemConstruct;

    NonlinearSolverActivator::registerservice(m_problem,"NonlinearSolverservice");


}
