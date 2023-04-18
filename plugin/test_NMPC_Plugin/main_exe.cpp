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
    initstate<<0,0,0,1;
    terminalstate.resize(4,1);
    terminalstate<<3.1415926535,0,3,0;


    m_widget=new Control_Widget;
    m_widget->show();
    connect(m_widget,SIGNAL(start_solving()),this,SLOT(startsolve()));
    test_NMPC_PluginActivator::publishsignal(this,SIGNAL(setstate(Eigen::MatrixXd)),OSGIEVENT::MAT_GET_NOW,Qt::QueuedConnection);
    m_ode=new test_ODE;
    m_Jac=new testODE_jac;
    qRegisterMetaType<Eigen::MatrixXd>("Eigen::MatrixXd");
    m_service=test_NMPC_PluginActivator::getService<NMPCservice>("NMPCservice");
    m_service1=test_NMPC_PluginActivator::getService<TCPserverservice>("TCPserverservice");
    m_service2=test_NMPC_PluginActivator::getService<CPYcoderservice>("CPYcoderservice");
    m_service1->startlisten(8001);
    Eigen::MatrixXd lowb;
    lowb.resize(1,1);
    lowb<<-10;

    Eigen::MatrixXd highb;
    highb.resize(1,1);
    highb<<10;

    m_service->set_control_bound(lowb,highb);
    m_service->registerODE(m_ode);
    m_service->registerODEJacob(m_Jac);
    m_service->init_state(initstate,terminalstate);
    m_service->init_num(4,1,100);
    m_service->init_steptime(0.03);//此处时间单位为秒
//    startsolve();

}



void main_exe::startsolve()
{
    m_service->solve_problem();
    Eigen::MatrixXd actmat=m_service->get_actMat();
    Eigen::MatrixXd statemat=m_service->get_stateMat();


    while (true)
    {
    for(int i=0;i<actmat.cols();i++)
    {
        qDebug()<<"action_at_time "<< i <<" is "<<actmat(0,i);
        qDebug()<<"dtheta_at_time "<< i <<" is "<<statemat(1,i);
        qDebug()<<"dx_at_time "<< i <<" is "<<statemat(3,i);
        QElapsedTimer et;
        et.start();

        Eigen::MatrixXd local_mat;
        local_mat.resize(4,1);
        local_mat.setZero();
        local_mat(0,0)=-statemat(2,i);
        local_mat(1,0)=statemat(1,i);
        local_mat(2,0)=statemat(0,i);
        local_mat(3,0)=statemat(3,i);


        m_service2->sendMAT(local_mat,m_service1);



        while(et.elapsed()<30)//ms
        {
            QCoreApplication::processEvents();
        }
    }
    }


}

