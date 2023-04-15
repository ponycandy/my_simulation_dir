#include "main_exe.h"
#include "test_NMPC_PluginActivator.h"
#include "service/CPYcoderservice.h"
#include "QCoreApplication"
#include "QElapsedTimer"
#include "Matrix_sparser.h"
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
    m_service1=test_NMPC_PluginActivator::getService<TCPserverservice>("TCPserverservice");
    m_service2=test_NMPC_PluginActivator::getService<CPYcoderservice>("CPYcoderservice");
    m_service1->startlisten(8001);
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
    m_service->init_num(4,1,50);
    m_service->init_steptime(0.1);//此处时间单位为秒

}

void main_exe::startsolve()
{
    m_service->solve_problem();
    Eigen::MatrixXd actmat=m_service->get_actMat();
    Eigen::MatrixXd statemat=m_service->get_stateMat();
    Eigen::MatrixXd local_mat;
    local_mat.resize(1,4);

    for(int i=0;i<actmat.cols();i++)
    {
        qDebug()<<"action_at_time "<< i <<" is "<<actmat(0,i);
        QElapsedTimer et;
        et.start();
        local_mat(0,0)=statemat(2,i);        local_mat(0,1)=statemat(3,i);
        local_mat(0,2)=statemat(0,i);        local_mat(0,3)=statemat(1,i);

        m_service2->sendMAT(local_mat,m_service1);


        while(et.elapsed()<30)//ms
        {
            QCoreApplication::processEvents();
        }
    }

//    Matrix_sparser m_sparser;

//    m_sparser.fillin(0,0,4);
//    m_sparser.setsize(3,3);
//    Eigen::SparseMatrix<double> mat=m_sparser.get_sparse_mat();
//    qDebug()<<mat.coeff(0,0);

//    m_sparser.clearall();
//    m_sparser.setsize(3,3);
//    Eigen::MatrixXd mat1;
//    mat1.resize(3,3);
//    mat1.setOnes();
//    m_sparser.add_mat_block(mat1.block(1,1,2,2),1,1);
//    Eigen::SparseMatrix<double> mat2=m_sparser.get_sparse_mat();
//    for(int i=0;i<3;i++)
//    {

//        qDebug()<<mat2.coeff(i,0)<<" "<<mat2.coeff(i,1)<<" "<<mat2.coeff(i,2)<<" ";

//    }
//    m_sparser.clearall();
//    Eigen::SparseMatrix<double> mat3=m_sparser.stack_vertical_blok(mat,mat2);

//    for(int i=0;i<6;i++)
//    {

//        qDebug()<<mat3.coeff(i,0)<<" "<<mat3.coeff(i,1)<<" "<<mat3.coeff(i,2)<<" ";

//    }
//    qDebug("stack_vertial_block");
////    m_sparser.add_mat_block_vertical();
//    Eigen::MatrixXd mat4=mat1*mat;//结果是dense矩阵
//    for(int i=0;i<3;i++)
//    {

//        qDebug()<<mat4.coeff(i,0)<<" "<<mat4.coeff(i,1)<<" "<<mat4.coeff(i,2)<<" ";

//    }
}

