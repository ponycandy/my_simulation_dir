#ifndef PROBLEM_WRAPUP_H
#define PROBLEM_WRAPUP_H

#include "dynamics_constrain.h"
#include "splinevariable.h"
#include "QVector"
class problem_wrapup
{
public:
    problem_wrapup();
    void construct();
    int statenum;
    int agentnum;
    int actnum;
    int dims;
    int pointnum;
    int decnum;
    int current_agent;
    double steptime;

    Dynamics_Constrain *m_constrain;
    QVector<SplineVariable*> m_spline_sets;

};

#endif // PROBLEM_WRAPUP_H
