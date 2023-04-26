
#include "mainexec.h"
#include "test_MPCActivator.h"
mainexec::mainexec(QObject *parent)
    : QObject{parent}
{
    funtor=new dynamic_function;
    m_service= test_MPCActivator::getService<MPC_Trackerservice>("MPC_Trackerservice");
    m_service->registerODE(funtor);
    m_service->init_num(4,1,20);
    m_service->init_steptime(30);
//    m_service->set_reference()

    m_wi=new Form;
    connect(m_wi,SIGNAL(start_calc()),this,SLOT(start_solve()));
    m_wi->show();
}

void mainexec::start_solve()
{
//    m_service->feed_Back_control()
}

