#ifndef SOLVERMANAGER_H
#define SOLVERMANAGER_H

#include <QObject>
#include <ifopt/ifopt_lib/ifopt/ipopt_solver.h>
class solverManager : public QObject
{
    Q_OBJECT
public:
    explicit solverManager(QObject *parent = nullptr);

signals:

};

#endif // SOLVERMANAGER_H
