#ifndef SOLVERMANAGER_H
#define SOLVERMANAGER_H
#include "service/NonlinearSolverservice.h"
#include "QObject"
#include "service/CPYcoderservice.h"
#include "swarm_ode.h"
#include "jacobiancalc.h"
#include "minimize_topology.h"
class Solvermanager:public QObject
{
    Q_OBJECT
public:
    Solvermanager();
    NonlinearSolverservice *m_solver;
    CPYcoderservice *m_decode;
    Swarm_ODE *ode;
    Jacobiancalc *Jac;
    minimize_Topology *costset;
    Eigen::MatrixXd cached_x;
    int decnum;
    int selfID;
    int initflag=0;
    void optimize(Eigen::MatrixXd &input,Eigen::MatrixXd &output);

public slots:
    void solvenow(Eigen::MatrixXd Dataseries);
};

#endif // SOLVERMANAGER_H
