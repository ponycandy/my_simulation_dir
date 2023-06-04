#ifndef PROBLEMCONSTRUCT_H
#define PROBLEMCONSTRUCT_H

#include <QObject>
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>

class ProblemConstruct : public QObject
{
    Q_OBJECT
public:
    explicit ProblemConstruct(QObject *parent = nullptr);

signals:

};

#endif // PROBLEMCONSTRUCT_H
