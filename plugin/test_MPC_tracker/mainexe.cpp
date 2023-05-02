
#include "mainexe.h"
#include "test_MPC_trackerActivator.h"
#include "include/OSGIEVENT.h"
#include "QCoreApplication"
#include "QElapsedTimer"

mainexe::mainexe(QObject *parent)
    : QObject{parent}
{
    m_service2=test_MPC_trackerActivator::getService<MPC_Trackerservice>("MPC_Trackerservice");

    test_MPC_trackerActivator::publishsignal(this,SIGNAL(mget_state_now())
                                             ,OSGIEVENT::REQUEST_PUSHINGBOX_STATE_NOW,Qt::DirectConnection);
    test_MPC_trackerActivator::subscribeslot(this,SLOT(state_return(Eigen::MatrixXd))
                                             ,OSGIEVENT::RETURN_PUSHINGBOX_STATE_NOW,Qt::DirectConnection);
    test_MPC_trackerActivator::publishsignal(this,SIGNAL(outer_stepin(Eigen::MatrixXd))
                                             ,OSGIEVENT::ACTION_PUSHINGBOX,Qt::DirectConnection);

    widgetm=new Form;
    functor=new dynamic_function;
    connect(widgetm,SIGNAL(start_solve()),this,SLOT(solve()));
    widgetm->show();
    m_service2->registerODE(functor);
    m_service2->init_steptime(0.03);
    m_service2->init_num(2,1,20);
    Eigen::MatrixXd state;
    state.resize(2,20);
    state.setZero();

    m_service2->set_reference(state,state,false);
    statenow.resize(2,1);
    statenow.setZero();
}

void mainexe::state_return(Eigen::MatrixXd state)
{
    statenow=state;
}

void mainexe::solve()
{
    Eigen::MatrixXd control;
    emit mget_state_now();

    while(true)
    {   QElapsedTimer et;
        et.start();
        control=m_service2->feed_Back_control(statenow);
        emit outer_stepin(control);
        while(et.elapsed()<30)//ms
        {
            QCoreApplication::processEvents();

        }
    }

}

