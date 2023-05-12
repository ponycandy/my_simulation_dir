
#ifndef MPC_TRACKERSERVICE_H
#define MPC_TRACKERSERVICE_H

#include <QObject>
#include <MPC/MPC_ODE.h>
class MPC_Trackerservice
{
public:
    virtual ~MPC_Trackerservice(){}
    virtual void init_steptime(double time)=0;
    virtual MPC_Trackerservice *clone_service()=0;
    virtual void registerODE(MPC_ODE *odefunction)=0;
    virtual void set_control_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher)=0;
    virtual void set_delta_control_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher)=0;
    virtual Eigen::MatrixXd feed_Back_control(Eigen::MatrixXd state)=0;
    virtual void init_num(int statenum, int actnum, int decisionnum) =0;
    virtual void set_state_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher)=0;
    virtual void setWeightMatrices(Eigen::MatrixXd Q, Eigen::MatrixXd R)=0;
    virtual void set_reference(Eigen::MatrixXd state,Eigen::MatrixXd action,bool use_action)=0;
    virtual void set_ref_target(Eigen::MatrixXd state)=0;

};
#define MPC_Trackerservice_iid "MPC_Trackerservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(MPC_Trackerservice,MPC_Trackerservice_iid  )
QT_END_NAMESPACE

#endif

