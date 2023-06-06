
#ifndef NONLINEARSOLVERSERVICE_H
#define NONLINEARSOLVERSERVICE_H

#include <QObject>
#include <Eigen/Core>
#include <include/NMPC/NMPC_ODE.h>
#include <include/NMPC/NMPC_dynamic_Jacob.h>
#include <include/NMPC/NMPC_Extra_Constrain.h>
//上面这些照抄NMPC_traj_gen的接口
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>
class NonlinearSolverservice
{
public:
    virtual ~NonlinearSolverservice(){}
    virtual void registerODE(NMPC_ODE *odefunction)=0;
    virtual void registerODEJacob(NMPC_Dynamic_Jacob *Dynamic_Jacob)=0;
    virtual void register_constrain(NMPC_Extra_Constrain *constrain)=0;
    virtual void init_num(int statenum,int actnum,int decisionnum)=0;
    virtual void init_state(Eigen::MatrixXd initstate,Eigen::MatrixXd terminalstate)=0;
    virtual Eigen::VectorXd solve_problem()=0;
    virtual Eigen::VectorXd solve_problem(QString varname)=0;
    virtual void start_crack()=0;
    virtual void init_steptime(double time)=0;
    virtual void init_all_x(int method,Eigen::MatrixXd input)=0;
    virtual NonlinearSolverservice* clone_service()=0;
    virtual Eigen::MatrixXd get_actMat()=0;
    virtual Eigen::MatrixXd get_stateMat()=0;
    virtual void set_control_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher)=0;
    virtual void Use_BuildIn_Dynamics_Cons(bool istrue)=0;
    virtual void AddVariableSet(ifopt::VariableSet::Ptr variable_set)=0;
    virtual void AddConstraintSet(ifopt::ConstraintSet::Ptr constraint_set)=0;
    virtual void AddCostSet(ifopt::CostTerm::Ptr cost_set)=0;
    virtual void setuseterminal(bool strue)=0;
    virtual void constructNLP()=0;
};
#define NonlinearSolverservice_iid "NonlinearSolverservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(NonlinearSolverservice,NonlinearSolverservice_iid  )
QT_END_NAMESPACE

#endif

