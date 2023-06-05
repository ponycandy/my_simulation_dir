#include "problemconstruct.h"

ProblemConstruct::ProblemConstruct(QObject *parent)
    : QObject{parent}
{
    use_internal_dynamics=false;
    set_Terminal=false;
    ipopt.SetOption("linear_solver", "mumps");
    ipopt.SetOption("jacobian_approximation", "exact");
}

void ProblemConstruct::registerODE(NMPC_ODE *odefunction)
{
    m_cons->registerODE(odefunction);
}

void ProblemConstruct::registerODEJacob(NMPC_Dynamic_Jacob *Dynamic_Jacob)
{
    m_cons->self_ode_jacob=Dynamic_Jacob;
}

void ProblemConstruct::register_constrain(NMPC_Extra_Constrain *constrain)
{
    //not working yet
}

void ProblemConstruct::init_num(int statenum, int actnum, int decisionnum)
{
    //这些数字必须在这里初始化，然后直接初始化对象
    //请在最开始初始化这个数字，后面才能够注册动力学
    state_num=statenum;
    act_num=actnum;
    dec_num=decisionnum;
    state_num_plus_act_num=actnum+statenum;
    constrain_num=dec_num*statenum;
    constrain_num_dynamics=constrain_num;
    total_varaible_num=state_num_plus_act_num*dec_num;
    if(set_Terminal==true)
    {
        m_cons=new Dynamics_Constrain_Set(constrain_num+state_num);
        m_cons->set_cons_num(statenum,actnum,decisionnum);
        m_cons->set_terminal_point=true;
        m_vars=new Dynamics_varaible_Set(total_varaible_num);
        m_vars->set_cons_num(statenum,actnum,decisionnum);
    }
    else
    {
        m_cons=new Dynamics_Constrain_Set(constrain_num);
        m_cons->set_cons_num(statenum,actnum,decisionnum);
        m_cons->set_terminal_point=false;
        m_vars=new Dynamics_varaible_Set(total_varaible_num);
        m_vars->set_cons_num(statenum,actnum,decisionnum);
    }
}

void ProblemConstruct::init_all_x(int method, Eigen::MatrixXd input)
{
    m_vars->SetVariables(input);
}

void ProblemConstruct::init_state(Eigen::MatrixXd initstate, Eigen::MatrixXd terminalstate)
{
    m_cons->init_state(initstate,terminalstate);
}

void ProblemConstruct::init_steptime(double time)
{
    m_cons->steptime=time;
}

void ProblemConstruct::setuseterminal(bool strue)
{
    set_Terminal=strue;
}

void ProblemConstruct::constructNLP()
{
    if(m_cons->set_terminal_point==true)
    {
        std::shared_ptr<ifopt::Component> variableptr(m_vars);
        std::shared_ptr<ifopt::ConstraintSet> consptr(m_cons);
//        std::shared_ptr<ifopt::ConstraintSet> costptr(mcost);
        nlp.AddVariableSet  (variableptr);
        nlp.AddConstraintSet(consptr);
        //        nlp.AddCostSet      (std::make_shared<ExCost>());
    }
    else
    {

    }
}

NonlinearSolverservice *ProblemConstruct::clone_service()
{
    ProblemConstruct *newconstruct=new ProblemConstruct;
    return newconstruct;
}

Eigen::VectorXd ProblemConstruct::solve_problem()
{
    ipopt.Solve(nlp);
    solutions = nlp.GetOptVariables()->GetValues();
    return solutions;
}

Eigen::MatrixXd ProblemConstruct::get_actMat()
{
    //使用者自行负责判断能否调用这个函数
    m_cons->pack_variable(solutions);
    return m_cons->actMat;
}

Eigen::MatrixXd ProblemConstruct::get_stateMat()
{
    m_cons->pack_variable(solutions);
    return m_cons->stateMat;
}

void ProblemConstruct::set_control_bound(Eigen::MatrixXd lower, Eigen::MatrixXd higher)
{
    m_vars->set_control_bound(lower,higher);
}

void ProblemConstruct::Use_BuildIn_Dynamics_Cons(bool istrue)
{
    use_internal_dynamics=istrue;
}

void ProblemConstruct::AddVariableSet(ifopt::Component::Ptr variable_set)
{
    nlp.AddVariableSet  (variable_set);
}

void ProblemConstruct::AddConstraintSet(ifopt::ConstraintSet::Ptr constraint_set)
{
    nlp.AddConstraintSet(constraint_set);
}

void ProblemConstruct::AddCostSet(ifopt::ConstraintSet::Ptr cost_set)
{
    nlp.AddCostSet(cost_set);
}
