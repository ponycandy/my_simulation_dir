#include "testifopt_2Activator.h"

#include <iostream>

#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>
#include <ifopt/test_vars_constr_cost.h>

testifopt_2Activator* testifopt_2Activator::m_instance=Q_NULLPTR;
PluginContext* testifopt_2Activator::m_CONTEXT=Q_NULLPTR;
testifopt_2Activator::testifopt_2Activator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void testifopt_2Activator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void testifopt_2Activator::start()
{
    ifopt::Problem nlp;
    nlp.AddVariableSet  (std::make_shared<ifopt::ExVariables>());
    nlp.AddConstraintSet(std::make_shared<ifopt::ExConstraint>());
    nlp.AddCostSet      (std::make_shared<ifopt::ExCost>());
    nlp.PrintCurrent();
//上面的ifopt_core都是可以加载出来的
    //出问题的是下面的ifopt_ipopt的内容！ipopt
//    // 2. choose solver and options
    ifopt::IpoptSolver ipopt;
    ipopt.SetOption("linear_solver", "mumps");
    ipopt.SetOption("jacobian_approximation", "exact");

    // 3 . solve
    ipopt.Solve(nlp);
    Eigen::VectorXd x = nlp.GetOptVariables()->GetValues();
    std::cout << x.transpose() << std::endl;

    // 4. test if solution correct
    double eps = 1e-5; //double precision
    assert(1.0-eps < x(0) && x(0) < 1.0+eps);
    assert(0.0-eps < x(1) && x(1) < 0.0+eps);
}
void testifopt_2Activator::stop()
{
delete this;

}
