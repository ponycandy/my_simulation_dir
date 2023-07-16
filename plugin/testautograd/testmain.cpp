#include "testmain.h"
#include "testautogradActivator.h"
Testmain::Testmain(QObject *parent)
    : QObject{parent}
{
    m_service= testautogradActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");

}
