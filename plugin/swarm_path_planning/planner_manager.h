#ifndef PLANNER_MANAGER_H
#define PLANNER_MANAGER_H

#include <QObject>
#include "service/NonlinearSolverservice.h"
#include "swarm_ode.h"
#include "jacobiancalc.h"
class planner_manager : public QObject
{
    Q_OBJECT
public:
    explicit planner_manager(QObject *parent = nullptr);
    NonlinearSolverservice *m_service;
    Swarm_ODE *m_ode;
    Jacobiancalc *m_Jac;
signals:

};

#endif // PLANNER_MANAGER_H
