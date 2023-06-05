#ifndef PROBLEMCONSTRUCT_H
#define PROBLEMCONSTRUCT_H

#include <QObject>
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>
#include <service/NonlinearSolverservice.h>
#include <dynamics_constrain_set.h>
#include "dynamics_varaible_set.h"
class ProblemConstruct : public QObject,public NonlinearSolverservice
{
    Q_OBJECT
public:
    explicit ProblemConstruct(QObject *parent = nullptr);
    void registerODE(NMPC_ODE *odefunction) override;
    void registerODEJacob(NMPC_Dynamic_Jacob *Dynamic_Jacob) override;
    void register_constrain(NMPC_Extra_Constrain *constrain) override;
    void init_num(int statenum, int actnum, int decisionnum) override;
    void init_all_x(int method, Eigen::MatrixXd input) override;
    void init_state(Eigen::MatrixXd initstate, Eigen::MatrixXd terminalstate) override;
    void init_steptime(double time) override;
    void setuseterminal(bool strue) override;
    void constructNLP() override;
    NonlinearSolverservice * clone_service() override;
    Eigen::VectorXd solve_problem() override;
    Eigen::MatrixXd get_actMat() override;
    Eigen::MatrixXd get_stateMat() override;
    void set_control_bound(Eigen::MatrixXd lower,Eigen::MatrixXd higher) override;

    void Use_BuildIn_Dynamics_Cons(bool istrue) override;
//首先考虑不使用内建动力学约束的情况
    //此时接口与ifort完全一致
    void AddVariableSet(ifopt::Component::Ptr variable_set) override;
    void AddConstraintSet(ifopt::ConstraintSet::Ptr constraint_set) override;
    void AddCostSet(ifopt::ConstraintSet::Ptr cost_set) override;
//第三部分接口，我们考虑使用自动梯度求解器进行梯度计算
    //这部分再说，现在比较难实现

    //掠过
    Dynamics_Constrain_Set *m_cons;
    Dynamics_varaible_Set *m_vars;
    ifopt::IpoptSolver ipopt;
    ifopt::Problem nlp;
    Eigen::VectorXd solutions;
    bool use_internal_dynamics;
    bool set_Terminal;


    int cons_num;
    int state_num;//状态变量的维度
    int act_num;//控制变量的维度
    int state_num_plus_act_num;
    int total_varaible_num;
    int constrain_num;
    int constrain_num_dynamics;
    int dec_num;//从轨迹开始到结束的总步长
    double steptime; //单位时间步长，典型为30ms

signals:

};

#endif // PROBLEMCONSTRUCT_H
