#include "solver_manager.h"
#include "Swarm_NMPC_PlannerActivator.h"
#include "dynamics_of_animals.h"
#include "jac_of_animals.h"
solver_manager::solver_manager()
{
    m_service=Swarm_NMPC_PlannerActivator::getService<NonlinearSolverservice>("NonlinearSolverservice");
    m_service->Use_BuildIn_Dynamics_Cons(true);
    m_service->setuseterminal(false);
    Jac_of_animals *jacobian_mat=new Jac_of_animals;
    Dynamics_of_Animals *dynamics_animals=new Dynamics_of_Animals;
    m_service->registerODE(jacobian_mat);
    m_service->registerODEJacob(dynamics_animals);
    Eigen::MatrixXd initstate;initstate.resize(4,1);
    Eigen::MatrixXd terminalstate;
    terminalstate=initstate;
    m_service->init_state(initstate,terminalstate);
    m_serivce->init_num(4,2,20);
    m_service->init_steptime(0.03);
}
