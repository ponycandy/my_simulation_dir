#ifndef SOLVER_MANAGER_H
#define SOLVER_MANAGER_H
#include "service/NonlinearSolverservice.h"
#include "PolyParams.h"
#include "QObject"
#include "QVector"
#include "startdreaw.h"
class solver_manager:public QObject
{
    Q_OBJECT
public:
    solver_manager();

    NonlinearSolverservice *m_service;
    int dims;
    int pointnum;
    int dec_num;
    int statenum;
    double steptime;
    int agentnum;
    startdreaw *m_widget;
signals:
    void sigs_polys(QVector<PolyParams> polys);
};

#endif // SOLVER_MANAGER_H
