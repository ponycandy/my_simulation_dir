#ifndef MAIN_EXE_H
#define MAIN_EXE_H

#include <QObject>
#include "service/NMPCservice.h"
#include "service/TCPserverservice.h"
#include <service/MPC_Trackerservice.h>
#include <dynamic_function.h>
#include "test_ode.h"
#include "testode_jac.h"
#include "control_widget.h"
#include "service/CPYcoderservice.h"

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
    Eigen::MatrixXd state_obs;
    TCPserverservice *m_service1;
    CPYcoderservice *m_service2;
    dynamic_function *funtor;
    MPC_Trackerservice *m_service3;
    int flag=0;
    char m_preassigned_mat[1000];
    void executesendmat(Eigen::MatrixXd mat);
signals:
    void get_state(Eigen::MatrixXd mat);

public slots:
    void startsolve();
    void recieve_Byte(QByteArray data);
    void matget(Eigen::MatrixXd mat);
};

#endif // MAIN_EXE_H
