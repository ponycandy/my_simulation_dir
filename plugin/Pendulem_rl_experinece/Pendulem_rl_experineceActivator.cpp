#include "Pendulem_rl_experineceActivator.h"


Pendulem_rl_experineceActivator* Pendulem_rl_experineceActivator::m_instance=Q_NULLPTR;
PluginContext* Pendulem_rl_experineceActivator::m_CONTEXT=Q_NULLPTR;
Pendulem_rl_experineceActivator::Pendulem_rl_experineceActivator(QObject *parent) : QObject(parent),manager(NULL)
{
    m_instance=this;
}
void Pendulem_rl_experineceActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Pendulem_rl_experineceActivator::start()
{
manager=new simmanager;
}
void Pendulem_rl_experineceActivator::stop()
{
delete this;

}
