#include "solvermanager.h"

solverManager::solverManager(QObject *parent)
    : QObject{parent}
{
    m_problem=new ProblemConstruct;
}
