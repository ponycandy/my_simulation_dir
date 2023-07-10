#include "main_exe.h"
#include "testNonlinearSOlverActivator.h"
#include "service/CPYcoderservice.h"
#include "QCoreApplication"
#include "QElapsedTimer"
#include "Matrix_sparser.h"
#include "defines/CpyDefines.h"
#include <include/OSGIEVENT.h>
#include <terminalset.h>
#include <cost_new.h>
#include <variable_new.h>
//尝试计算倒立摆的状态
main_exe::main_exe(QObject *parent) : QObject(parent)
{
    initstate.resize(4,1);
    state_obs.resize(4,1);
    state_obs<<3.1415926535,0,0,0;
    initstate<<0,0,0,0;
    terminalstate.resize(4,1);
    terminalstate<<3.1415926535,0,0,0;


    m_widget=new Control_Widget;
    m_widget->show();
    connect(m_widget,SIGNAL(start_solving()),this,SLOT(startsolve()));
    testNonlinearSOlverActivator::publishsignal(this,SIGNAL(get_state(Eigen::MatrixXd)),OSGIEVENT::GET_PENDULUM_STATE_NOW,Qt::QueuedConnection);
    m_ode=new test_ODE;
    m_Jac=new testODE_jac;
    qRegisterMetaType<Eigen::MatrixXd>("Eigen::MatrixXd");
    m_service=testNonlinearSOlverActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    m_service1=testNonlinearSOlverActivator::getService<TCPserverservice>("TCPserverservice");
    m_service2=testNonlinearSOlverActivator::getService<CPYcoderservice>("CPYcoderservice");
    m_service1->startlisten(8001);
    m_service1->Bind_Slot(this,SLOT(recieve_Byte(QByteArray)));
    m_service2=m_service2->cloneservice();
    m_service2->Bind_Slot(this,SLOT(matget(Eigen::MatrixXd)));
    //必须要使用中间转接，这个属于固有问题
    Eigen::MatrixXd lowb;
    lowb.resize(1,1);
    lowb<<-30;

    Eigen::MatrixXd highb;
    highb.resize(1,1);
    highb<<30;

    m_service->set_control_bound(lowb,highb);
    m_service->registerODE(m_ode);

    m_service->registerODEJacob(m_Jac);
    m_service->init_state(initstate,terminalstate);
    m_service->init_num(4,1,100);
    m_service->init_steptime(0.03);//此处时间单位为秒
    m_service->setuseterminal(false);
    m_service->Use_BuildIn_Dynamics_Cons(true);
    TerminalSet *newset=new TerminalSet;
    std::shared_ptr<ifopt::ConstraintSet> consptr(newset);
    m_service->AddConstraintSet(consptr);
    m_service->AddCostSet(std::make_shared<cost_New>());
    m_service->AddVariableSet(std::make_shared<Variable_new>());
    m_service->constructNLP();
    //    startsolve();

    funtor=new dynamic_function;
    m_service3= testNonlinearSOlverActivator::getService<MPC_Trackerservice>("MPC_Trackerservice");
    m_service3->registerODE(funtor);
    m_service3->init_num(4,1,30);
    m_service3->init_steptime(0.03);//此处时间单位为秒
    Eigen::MatrixXd Q;Q.resize(4,4);
    Q<<1,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0;//不稳定基本只在终点参考耗尽的时候出现
    //并且算法稳定性的确高度依赖调参
    Eigen::MatrixXd R;R.resize(1,1);
    R<<1;
    m_service3->setWeightMatrices(Q,R);
    Eigen::MatrixXd lower;lower.resize(1,1);lower<<-200;
    Eigen::MatrixXd higher;higher.resize(1,1);higher<<200;

    m_service3->set_control_bound(lower,higher);


}


void main_exe::startsolve()
{
//    m_service->constructNLP();
    m_service->start_crack();
    Eigen::MatrixXd actmat=m_service->get_actMat();
    Eigen::MatrixXd statemat=m_service->get_stateMat();
    //    Eigen::MatrixXd statemat;
    Eigen::MatrixXd controlmat;
    Eigen::MatrixXd getstatemat;
    Eigen::MatrixXd init_state;
    getstatemat.resize(2,1);
    init_state.resize(4,1);
    init_state<<0,0,0,0;
    int i=0;
    while (true)
    {

        Eigen::MatrixXd stateset;
        for(int j=0;j<100;j++)
        {
            stateset=statemat.block(0,j,4,1);
            m_service2->sendMAT(stateset,m_service1);
            QElapsedTimer etx;
            etx.start();
            while(etx.elapsed()<30)//ms
            {
                QCoreApplication::processEvents();
            }
        }
        stateset.setZero();
        m_service2->sendMAT(stateset,m_service1);

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

