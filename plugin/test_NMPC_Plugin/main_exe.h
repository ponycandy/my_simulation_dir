#ifndef MAIN_EXE_H
#define MAIN_EXE_H

#include <QObject>
#include "service/NMPCservice.h"
#include "include/NMPC/NMPC_ODE.h"
#include "include/NMPC/NMPC_dynamic_Jacob.h"
#include "test_ode.h"
#include "testode_jac.h"
#include "control_widget.h"
class main_exe : public QObject
{
    Q_OBJECT
public:
    explicit main_exe(QObject *parent = nullptr);
    NMPCservice *m_service;
    test_ODE *m_ode;
    testODE_jac *m_Jac;
    Control_Widget *m_widget;
    Eigen::MatrixXd initstate;
    Eigen::MatrixXd terminalstate;

signals:

public slots:
    void startsolve();
};

#endif // MAIN_EXE_H
