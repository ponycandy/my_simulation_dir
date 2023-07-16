#ifndef TESTMAIN_H
#define TESTMAIN_H

#include <QObject>
#include "service/NonlinearSolverservice.h"
class Testmain : public QObject
{
    Q_OBJECT
public:
    explicit Testmain(QObject *parent = nullptr);

    NonlinearSolverservice *m_service;

signals:

};

#endif // TESTMAIN_H
