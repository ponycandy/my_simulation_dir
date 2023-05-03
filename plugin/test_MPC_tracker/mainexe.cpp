
#include "mainexe.h"
#include "test_MPC_trackerActivator.h"
#include "include/OSGIEVENT.h"
#include "QCoreApplication"
#include "QElapsedTimer"
#include <chrono>   //计算时间


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
    Eigen::MatrixXd Q;Q.resize(2,2);
    Q<<10,0,0,0.5;
    Eigen::MatrixXd R;R.resize(1,1);
    R<<1;

    m_service2->set_reference(state,state,false);
    m_service2->setWeightMatrices(Q,R);
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
        //        using namespace ;

        auto starttime = std::chrono::system_clock::now();


        control=m_service2->feed_Back_control(statenow);
        std::chrono::duration<double> diff = std::chrono::system_clock::now()- starttime;
        qDebug() << "所耗时间为：" << diff.count() << "s" ;
        //控制周期约5ms，满足要求，但是可以看到
        //在矩阵运算中消耗的时间大概是20~30倍的求解器时间
        //这个求解器的速度是真的快
        //考虑到矩阵有进一步sparse的空间，还可以优化矩阵的乘法
        //在这里我们就不追求这个极致了，目前已经完全够用
        emit outer_stepin(control);
        while(et.elapsed()<30)//ms
        {
            QCoreApplication::processEvents();

        }
    }

}

