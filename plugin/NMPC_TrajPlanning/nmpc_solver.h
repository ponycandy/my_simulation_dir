#ifndef NMPC_SOLVER_H
#define NMPC_SOLVER_H

#include <QObject>
#include "IpIpoptApplication.hpp"
#include "IpSolveStatistics.hpp"
class NMPC_solver : public QObject
{
    Q_OBJECT
public:
    explicit NMPC_solver(QObject *parent = nullptr);
    void solveNow(Ipopt::SmartPtr<Ipopt::TNLP> nlpproblem);
    Ipopt::SmartPtr<Ipopt::IpoptApplication> ipopt_solver;
signals:

};

#endif // NMPC_SOLVER_H
