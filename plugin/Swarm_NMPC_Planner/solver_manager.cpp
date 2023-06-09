#include "solver_manager.h"
#include "Swarm_NMPC_PlannerActivator.h"
#include "dynamics_of_animals.h"
#include "jac_of_animals.h"
#include "path_point_constrain.h"
#include "problem_wrapup.h"
solver_manager::solver_manager()
{
    m_service=Swarm_NMPC_PlannerActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    m_service->Use_BuildIn_Dynamics_Cons(false);
    m_service->setuseterminal(false);

    Eigen::MatrixXd initstate;
    int dec_num=20;
    int statenum=4;
    int act_num=2;
    int agent_num=3;

    problem_wrapup *m_problem=new problem_wrapup;


}
