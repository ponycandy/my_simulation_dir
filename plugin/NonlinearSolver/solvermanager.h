#ifndef SOLVERMANAGER_H
#define SOLVERMANAGER_H

#include <QObject>
#include <problemconstruct.h>
class solverManager : public QObject
{
    Q_OBJECT
public:
    explicit solverManager(QObject *parent = nullptr);
    ProblemConstruct *m_problem;

signals:

};

#endif // SOLVERMANAGER_H
