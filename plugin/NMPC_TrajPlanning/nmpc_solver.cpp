#include "nmpc_solver.h"
#include "QtDebug"
NMPC_solver::NMPC_solver(QObject *parent) : QObject(parent)
{
    //    Ipopt::SmartPtr<Ipopt::TNLP> mynlp = new TestNLP();


    ipopt_solver = new Ipopt::IpoptApplication();
    Ipopt::ApplicationReturnStatus status;
    status = ipopt_solver->Initialize();
    if (status != Ipopt::Solve_Succeeded)
    {
        qDebug()<<("\n\n*** Error during initialization!\n");

    }
}

void NMPC_solver::solveNow(Ipopt::SmartPtr<Ipopt::TNLP> nlpproblem)
{
    Ipopt::ApplicationReturnStatus status = ipopt_solver->OptimizeTNLP(nlpproblem);

    if (status == Ipopt::Solve_Succeeded)
    {
        // Retrieve some statistics about the solve
        Ipopt::Index iter_count = ipopt_solver->Statistics()->IterationCount();
        QString textnow;
        qDebug()<<"\n\n*** The problem solved in "+QString::number(iter_count)+" iterations!\n";
        Ipopt::Number final_obj = ipopt_solver->Statistics()->FinalObjective();
        qDebug()<<"\n\n*** The final value of the objective function is "+QString::number(final_obj);
    }
}

