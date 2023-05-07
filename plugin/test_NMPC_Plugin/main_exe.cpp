#include "main_exe.h"
#include "test_NMPC_PluginActivator.h"
#include "service/CPYcoderservice.h"
#include "QCoreApplication"
#include "QElapsedTimer"
#include "Matrix_sparser.h"
#include "defines/CpyDefines.h"
#include <include/OSGIEVENT.h>
//尝试计算倒立摆的状态
main_exe::main_exe(QObject *parent) : QObject(parent)
{
    initstate.resize(4,1);
    state_obs.resize(4,1);
    initstate<<0,0,0,0;
    terminalstate.resize(4,1);
    terminalstate<<3.1415926535,0,0,0;


    m_widget=new Control_Widget;
    m_widget->show();
    connect(m_widget,SIGNAL(start_solving()),this,SLOT(startsolve()));
    test_NMPC_PluginActivator::publishsignal(this,SIGNAL(get_state(Eigen::MatrixXd)),OSGIEVENT::GET_PENDULUM_STATE_NOW,Qt::QueuedConnection);
    m_ode=new test_ODE;
    m_Jac=new testODE_jac;
    qRegisterMetaType<Eigen::MatrixXd>("Eigen::MatrixXd");
    m_service=test_NMPC_PluginActivator::getService<NMPCservice>("NMPCservice");
    m_service1=test_NMPC_PluginActivator::getService<TCPserverservice>("TCPserverservice");
    m_service2=test_NMPC_PluginActivator::getService<CPYcoderservice>("CPYcoderservice");
    m_service1->startlisten(8001);
    m_service1->Bind_Slot(this,SLOT(recieve_Byte(QByteArray)));
    m_service2=m_service2->cloneservice();
    m_service2->Bind_Slot(this,SLOT(matget(Eigen::MatrixXd)));
    //必须要使用中间转接，这个属于固有问题
    Eigen::MatrixXd lowb;
    lowb.resize(1,1);
    lowb<<-20;

    Eigen::MatrixXd highb;
    highb.resize(1,1);
    highb<<20;

    m_service->set_control_bound(lowb,highb);
    m_service->registerODE(m_ode);

    m_service->registerODEJacob(m_Jac);
    m_service->init_state(initstate,terminalstate);
    m_service->init_num(4,1,300);
    m_service->init_steptime(0.03);//此处时间单位为秒
    //    startsolve();

    funtor=new dynamic_function;
    m_service3= test_NMPC_PluginActivator::getService<MPC_Trackerservice>("MPC_Trackerservice");
    m_service3->registerODE(funtor);
    m_service3->init_num(4,1,30);
    m_service3->init_steptime(0.03);//此处时间单位为秒
    Eigen::MatrixXd Q;Q.resize(4,4);
    Q<<3,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0;//不稳定基本只在终点参考耗尽的时候出现
    //并且算法稳定性的确高度依赖调参
    Eigen::MatrixXd R;R.resize(1,1);
    R<<0;
    m_service3->setWeightMatrices(Q,R);
    Eigen::MatrixXd lower;lower.resize(1,1);lower<<-100;
    Eigen::MatrixXd higher;higher.resize(1,1);higher<<100;

    m_service3->set_control_bound(lower,higher);
}



void main_exe::startsolve()
{
    m_service->solve_problem();
    Eigen::MatrixXd actmat=m_service->get_actMat();
    Eigen::MatrixXd statemat=m_service->get_stateMat();
//    Eigen::MatrixXd actmat_stack_last_one;Eigen::MatrixXd pinghengdian;
//    actmat_stack_last_one.resize(1,101);pinghengdian.resize(1,1);pinghengdian.setZero();
//    actmat_stack_last_one<<actmat,pinghengdian;
    Eigen::MatrixXd controlmat;
    Eigen::MatrixXd getstatemat;
    Eigen::MatrixXd init_state;
    getstatemat.resize(2,1);
    init_state.resize(4,1);
    init_state<<0,0,0,0;
    //    statemat.resize(4,30);
    //    actmat.resize(1,30);
    //    actmat.setZero();
    //    for(int i=0;i<30;i++)
    //    {
    //        statemat.block(0,i,4,1)<<3.1415926535,0,0,0;
    //    }

    m_service3->set_reference(statemat,actmat,true);
    int i=0;
    while (true)
    {

        QElapsedTimer et;
        et.start();
        QElapsedTimer et2;
        et2.start();
        flag=0;
        m_service2->sendMAT(getstatemat,m_service1);
        while(et2.elapsed()<15)//ms
        {
            QCoreApplication::processEvents();
            if(flag==1)
            {
                break;
            }
        }
        flag=0;
        i++;
        controlmat=m_service3->feed_Back_control(state_obs);
        //        controlmat=actmat.block(0,i++,1,1);
        m_service2->sendMAT(controlmat,m_service1);

        while(et.elapsed()<15)//ms
        {
            QCoreApplication::processEvents();
        }
        if(i>99)
        {
            i=0;
            //            Eigen::MatrixXd stateset;
            //            for(int j=0;j<100;j++)
            //            {
            //                stateset=statemat.block(0,j,4,1);
            //                m_service2->sendMAT(stateset,m_service1);
            //                QElapsedTimer etx;
            //                etx.start();
            //                while(etx.elapsed()<30)//ms
            //                {
            //                    QCoreApplication::processEvents();
            //                }
            //            }
            //            stateset.setZero();
            //            m_service2->sendMAT(stateset,m_service1);
            //        }
        }

    }


}

void main_exe::recieve_Byte(QByteArray data)
{
    flag=1;
    m_service2->getmat(data);
}

void main_exe::matget(Eigen::MatrixXd mat)
{
    state_obs=mat;
}

