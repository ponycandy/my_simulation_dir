#ifndef MAIN_STREAM_H
#define MAIN_STREAM_H

#include <QObject>
#include <mypainter.h>
#include <simulator.h>
#include <vehicle.h>
#include <simulatorwidget.h>
#include "service/SimDynamicsservice.h"
#include "service/Tcpcommunicateservice.h"

#include <QTimer>
class main_stream : public QObject
{
    Q_OBJECT
public:
    explicit main_stream(QObject *parent = nullptr);
    vehicle *singleone;
    simulatorWidget *widgetm;
     QTimer *   a_test_timer;
     SimDynamicsservice *dysim;
     Tcpcommunicateservice *TCPsoc;
signals:
public slots:
     void step_once();
     void matrecieved(Eigen::MatrixXd mat);
};

#endif // MAIN_STREAM_H
