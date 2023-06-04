#include "NonlinearSolverActivator.h"


NonlinearSolverActivator* NonlinearSolverActivator::m_instance=Q_NULLPTR;
PluginContext* NonlinearSolverActivator::m_CONTEXT=Q_NULLPTR;
NonlinearSolverActivator::NonlinearSolverActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void NonlinearSolverActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void NonlinearSolverActivator::start()
{
    m_manager=new solverManager;
}
void NonlinearSolverActivator::stop()
{
delete this;

}
