#ifndef NONLINEARPLANNER_H
#define NONLINEARPLANNER_H

#include "Eigen/core"
#include "service/NonlinearSolverservice.h"
#include "service/Datalogservice.h"
#include "swarm_ode.h"
#include "jacobiancalc.h"
#include "minimize_topology.h"
class NonlinearPlanner
{
public:
    NonlinearPlanner();
    void plan(Eigen::MatrixXd &statesOfall,Eigen::MatrixXd &Target,Eigen::MatrixXd &planed);
    NonlinearSolverservice *m_service;
    Datalogservice *logger;
    Swarm_ODE *m_ode;
    minimize_Topology *newset2;
    Jacobiancalc *m_Jac;

    int agentnum;
    int steptime;
    int decnum; //这个就是预测长度
};

#endif // NONLINEARPLANNER_H
