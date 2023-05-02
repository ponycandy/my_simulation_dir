#ifndef SIMMANAGER_H
#define SIMMANAGER_H

#include <QObject>
#include <mypainter.h>
#include <simulator.h>
#include <service/CPYcoderservice.h>
#include "service/Tcpcommunicateservice.h"
#include "service/SimDynamicsservice.h"
class simmanager : public QObject
{
    Q_OBJECT
public:
    explicit simmanager(QObject *parent = nullptr);
    MYpainter *paint;
    Simulator *m_sim;
    CPYcoderservice *decoder;
    Tcpcommunicateservice *m_TCP;
    SimDynamicsservice *ODE_service;
    void setupEvent();
signals:
    void state_return(Eigen::MatrixXd mat);
public slots:
    void matrecieved(Eigen::MatrixXd mat);
    void get_state_now();
    void outer_stepin(Eigen::MatrixXd mat);
};

#endif // SIMMANAGER_H
