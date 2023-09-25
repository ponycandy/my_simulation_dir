#include "problemconstruct.h"
#include "terminalset.h"
#include "xmlcore.h"
ProblemConstruct::ProblemConstruct(QObject *parent)
    : QObject{parent}
{
    use_internal_dynamics=false;
    set_Terminal=false;
    returstatus=0;
    QString configfiename="./config/Ipopt/Ipoptconfig.xml";
    xmlCore xml_reader(configfiename.toStdString());
    std::string linear_solver;
    std::string jacobian_approximation;
    std::string nlp_scaling_method;
    std::string check_derivatives_for_naninf;
    std::string hessian_approximation;
    double acceptable_obj_change_tol;
    int print_level;
    double tol;
    double constr_viol_tol;
    int max_iter;
    xml_reader.xmlRead("linear_solver",linear_solver);
    xml_reader.xmlRead("hessian_approximation",hessian_approximation);
    xml_reader.xmlRead("acceptable_obj_change_tol",acceptable_obj_change_tol);
    xml_reader.xmlRead("jacobian_approximation",jacobian_approximation);
    xml_reader.xmlRead("print_level",print_level);
    xml_reader.xmlRead("tol",tol);
    xml_reader.xmlRead("constr_viol_tol",constr_viol_tol);
    xml_reader.xmlRead("nlp_scaling_method",nlp_scaling_method);
    xml_reader.xmlRead("check_derivatives_for_naninf",check_derivatives_for_naninf);
    xml_reader.xmlRead("max_iter", max_iter);
    ipopt.SetOption("max_iter", max_iter);
    ipopt.SetOption("linear_solver", linear_solver);
    ipopt.SetOption("nlp_scaling_method", nlp_scaling_method);
    ipopt.SetOption("jacobian_approximation", jacobian_approximation);
    ipopt.SetOption("tol",tol);
    ipopt.SetOption("print_level",print_level);
    ipopt.SetOption("check_derivatives_for_naninf",check_derivatives_for_naninf);
    ipopt.SetOption("acceptable_obj_change_tol",acceptable_obj_change_tol);
    ipopt.SetOption("hessian_approximation",hessian_approximation);
    ipopt.SetOption("constr_viol_tol", constr_viol_tol); // or any value you prefer
}

void ProblemConstruct::registerODE(NMPC_ODE *odefunction)
{
    selfodefunction=odefunction;
    //    m_cons->registerODE(odefunction);
}

int ProblemConstruct::crack_and_return()
{
    ipopt.Solve(nlp);
    returstatus=ipopt.GetReturnStatus();
    return returstatus;
//    0.Solve_Succeeded
//        -1.Maximum_Iterations_Exceeded
//    1: Solved_To_Acceptable_Level
//        2: Infeasible_Problem_Detected
//            3: Search_Direction_Becomes_Too_Small
//                4: Diverging_Iterates
//                    5: User_Requested_Stop
//                        6: Feasible_Point_Found
//                            -2: Restoration_Failed
//                                  -3: Error_In_Step_Computation
//                                        -4: Maximum_CpuTime_Exceeded
//                                              -10: Not_Enough_Degrees_Of_Freedom
//                                                     -11: Invalid_Problem_Definition
//                                                            -12: Invalid_Option
//                                                                   -13: Invalid_Number_Detected
//                                                                          -100: Unrecoverable_Exception
//                                                                                  -101: NonIpopt_Exception_Thrown
//                                                                                          -102: Insufficient_Memory
//                                                                                                  -199: Internal_Error
}

void ProblemConstruct::registerODEJacob(NMPC_Dynamic_Jacob *Dynamic_Jacob)
{
    selfDynamic_Jacob=Dynamic_Jacob;
    //    m_cons->self_ode_jacob=Dynamic_Jacob;
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
    selflower.resize(actnum,1);
    selflower.setConstant(-99999);
    selfhigher=-selflower;

}

void ProblemConstruct::init_all_x(int method, std::shared_ptr<Eigen::MatrixXd> input)
{
    m_vars->all_variable=input->eval();
    //如果没有调用，将以0开始
    //如果调用了，也不会从头开始构建问题
    //可以说是比较节省cpu的一种做法
}

void ProblemConstruct::init_state(Eigen::MatrixXd initstate, Eigen::MatrixXd terminalstate)
{
    init_state_p=initstate;
    terminal_state_p=terminalstate;
}

void ProblemConstruct::init_steptime(double time)
{
    steptime=time;
}

void ProblemConstruct::setuseterminal(bool strue)
{
    set_Terminal=strue;
}

void ProblemConstruct::constructNLP()
{
    if(use_internal_dynamics==true)
    {

        if(set_Terminal==true)
        {
            m_cons=new Dynamics_Constrain_Set(constrain_num+state_num);
            m_cons->set_cons_num(state_num,act_num,dec_num);
            m_cons->set_use_terminal(true);
            m_vars=new Dynamics_varaible_Set(total_varaible_num);
            m_vars->set_cons_num(state_num,act_num,dec_num);
        }
        else
        {
            m_cons=new Dynamics_Constrain_Set(constrain_num);
            m_cons->set_cons_num(state_num,act_num,dec_num);
            m_cons->set_use_terminal(false);
            m_vars=new Dynamics_varaible_Set(total_varaible_num);
            m_vars->set_cons_num(state_num,act_num,dec_num);
        }
        m_cons->initState=init_state_p;
        m_cons->TerminalState=terminal_state_p;
        m_cons->steptime=steptime;
        m_cons->registerODE(selfodefunction);
        m_cons->self_ode_jacob=selfDynamic_Jacob;
        m_vars->set_control_bound(selflower,selfhigher);
        std::shared_ptr<ifopt::Component> variableptr(m_vars);
        std::shared_ptr<ifopt::ConstraintSet> consptr(m_cons);
        nlp.AddVariableSet  (variableptr);
        nlp.AddConstraintSet(consptr);
        nlp.PrintCurrent();
    }
    else
    {

    }
}

void ProblemConstruct::GetVariable(QString name, Eigen::MatrixXd &returnvalue)
{
    returnvalue=nlp.GetOptVariables()->GetComponent(name.toStdString())->GetValues();
}

void ProblemConstruct::ReinitState(Eigen::MatrixXd &initstate, Eigen::MatrixXd &terminalstate)
{
    m_cons->initState=initstate.eval();
    m_cons->TerminalState=terminalstate.eval();
}

NonlinearSolverservice *ProblemConstruct::clone_service()
{
    ProblemConstruct *newconstruct=new ProblemConstruct;
    return newconstruct;
}

Eigen::VectorXd ProblemConstruct::solve_problem()
{
    ipopt.Solve(nlp);
    solutions=nlp.GetOptVariables()->GetComponent("action_state_set1")->GetValues();
    return solutions;
}

Eigen::VectorXd ProblemConstruct::solve_problem(QString name)
{
    solutions=nlp.GetOptVariables()->GetComponent(name.toStdString())->GetValues();
    return solutions;
}

void ProblemConstruct::start_crack()
{
    ipopt.Solve(nlp);
    returstatus=ipopt.GetReturnStatus();
}

Eigen::MatrixXd ProblemConstruct::get_actMat()
{
    //使用者自行负责判断能否调用这个函数
    solutions=nlp.GetOptVariables()->GetComponent("action_state_set1")->GetValues();
    m_cons->pack_variable(solutions);
    return m_cons->actMat;
}

Eigen::MatrixXd ProblemConstruct::get_stateMat()
{
    solutions=nlp.GetOptVariables()->GetComponent("action_state_set1")->GetValues();
    m_cons->pack_variable(solutions);
    return m_cons->stateMat;
}

void ProblemConstruct::set_control_bound(Eigen::MatrixXd lower, Eigen::MatrixXd higher)
{
    selflower=lower;
    selfhigher=higher;

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
