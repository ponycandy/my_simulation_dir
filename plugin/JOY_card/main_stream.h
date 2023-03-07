#ifndef MAIN_STREAM_H
#define MAIN_STREAM_H

#include <QObject>
#include <mypainter.h>
#include <simulator.h>
#include <QTimer>
#include "service/SwarmSimservice.h"
//#include "classA_test.h"
class main_stream : public QObject
{
    Q_OBJECT
public:
    explicit main_stream(QObject *parent = nullptr);
    MYpainter *paint;
    Simulator *m_sim;
    QTimer *a_test_timer;
    SwarmSimservice *a_service;
    void setupEvent();
signals:

public slots:
    void step_once();
};

#endif // MAIN_STREAM_H
