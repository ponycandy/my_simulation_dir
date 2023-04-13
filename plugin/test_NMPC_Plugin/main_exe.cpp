#include "main_exe.h"
#include "test_NMPC_PluginActivator.h"
#include "math.h"
//尝试计算倒立摆的状态
main_exe::main_exe(QObject *parent) : QObject(parent)
{
    initstate.resize(4,1);
    initstate<<0,0,0,0;
    terminalstate.resize(4,1);
    terminalstate<<0,0,3.1415926535,0;


    m_widget=new Control_Widget;
    m_widget->show();
    connect(m_widget,SIGNAL(start_solving()),this,SLOT(startsolve()));
    m_ode=new test_ODE;
    m_Jac=new testODE_jac;
    m_service=test_NMPC_PluginActivator::getService<NMPCservice>("NMPCservice");
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
    m_service->init_num(4,1,20);
    m_service->init_steptime(0.1);//此处时间单位为秒

}

void main_exe::startsolve()
{
    m_service->solve_problem();
    Eigen::MatrixXd actmat=m_service->get_actMat();

    for(int i=0;i<actmat.cols();i++)
    {
        qDebug()<<"action_at_time "<< i <<" is "<<actmat(0,i);
    }
}
