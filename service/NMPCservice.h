
#ifndef NMPCSERVICE_H
#define NMPCSERVICE_H

#include <QObject>
#include <Eigen/Core>
#include <include/NMPC/NMPC_ODE.h>
#include <include/NMPC/NMPC_dynamic_Jacob.h>
#include <include/NMPC/NMPC_Extra_Constrain.h>
class NMPCservice
{
public:
    virtual ~NMPCservice(){}
    virtual void registerODE(NMPC_ODE *odefunction)=0;
    virtual void registerODEJacob(NMPC_Dynamic_Jacob *Dynamic_Jacob)=0;
    virtual void register_constrain(NMPC_Extra_Constrain *constrain)=0;
    virtual void init_num(int statenum,int actnum,int decisionnum)=0;
    virtual void init_state(Eigen::MatrixXd initstate,Eigen::MatrixXd terminalstate)=0;
    virtual void solve_problem()=0;
    virtual void init_steptime(double time)=0;
    virtual void init_all_x(int method,Eigen::MatrixXd input)=0;
    virtual NMPCservice* clone_service()=0;
    virtual Eigen::MatrixXd get_actMat()=0;
    virtual Eigen::MatrixXd get_stateMat()=0;
    virtual void set_control_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher)=0;

};
#define NMPCservice_iid "NMPCservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(NMPCservice,NMPCservice_iid  )
QT_END_NAMESPACE

#endif

