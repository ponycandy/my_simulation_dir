﻿#ifndef SOLVER_MANAGER_H
#define SOLVER_MANAGER_H
#include "service/NonlinearSolverservice.h"

class solver_manager
{
public:
    solver_manager();

    NonlinearSolverservice *m_service;
    int dims;
    int pointnum;
    int dec_num;
    double steptime;
};

#endif // SOLVER_MANAGER_H
