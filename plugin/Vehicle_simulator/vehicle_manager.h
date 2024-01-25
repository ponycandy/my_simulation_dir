#ifndef VEHICLE_MANAGER_H
#define VEHICLE_MANAGER_H

#include "service/SimDynamicsservice.h"
#include "simulator.h"
#include "QObject"
#include "service/CPYcoderservice.h"
#include "QWidget"
#include "service/Animateservice.h"
#include "mypainter.h"
class vehicle_manager:public QObject
{
    Q_OBJECT
public:
    vehicle_manager();
    SimDynamicsservice *simer;
    Simulator *m_sim;
    CPYcoderservice *m_decoder;
    Animateservice *m_anim;
    QWidget *m_widget;
    MYpainter *m_painter;
private slots:
    void get_control(Eigen::MatrixXd act);

};

#endif // VEHICLE_MANAGER_H
