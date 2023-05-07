
#include "managers.h"
#include "test_MPC_nonlinear_trackingActivator.h"
managers::managers(QObject *parent)
    : QObject{parent}
{
    m_service=test_MPC_nonlinear_trackingActivator::getService<SimDynamicsservice>("SimDynamicsservice");
    odef=new twotwoode;
    mpc=test_MPC_nonlinear_trackingActivator::getService<MPC_Trackerservice>("MPC_Trackerservice");
    mpc->registerODE(odef);
    mpc->init_num(1,1,12);
    Eigen::MatrixXd ref,act;
    ref.resize(1,12);
    ref.setOnes();
    ref=3*ref;
    act.resize(1,12);
    act.setZero();
    mpc->set_reference(ref,act,false);
    ref.resize(1,1);
    ref<<-10;
    act=-ref;
    mpc->set_control_bound(ref,act);
    Eigen::MatrixXd statenow=odef->state;
    Eigen::MatrixXd Q;Q.resize(1,1);
    Q<<1;
    Eigen::MatrixXd R=Q;
    R<<1;//R不能够设置为0，否则问题会不稳定
    //就算是线性问题，也高度依赖参数的调整
    mpc->setWeightMatrices(Q,R);
    while(true)
    {
        Eigen::MatrixXd controls=mpc->feed_Back_control(statenow);
        odef->control_0=controls;
        statenow=odef->stepin();
        qDebug()<<"x is: "<<statenow(0,0)<< " control is "<<odef->control_0(0,0);
    }

}

