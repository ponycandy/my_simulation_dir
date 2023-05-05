#ifndef MAIN_STREAM_H
#define MAIN_STREAM_H

#include <QObject>
#include <mypainter.h>
#include <simulator.h>
#include <vehicle.h>
#include <simulatorwidget.h>
#include "service/SimDynamicsservice.h"
#include "service/Tcpcommunicateservice.h"
#include "service/CPYcoderservice.h"
#include <QTimer>
#include <mypainter.h>
class main_stream : public QObject
{
    Q_OBJECT
public:
    explicit main_stream(QObject *parent = nullptr);
    void init_ref();
    vehicle *singleone;
    MYpainter *m_paint;
    Animateservice *Anim_service_0;
    simulatorWidget *widgetm;
     QTimer *   a_test_timer;
     SimDynamicsservice *dysim;
     Tcpcommunicateservice *TCPsoc;
     CPYcoderservice *decoder;
     Eigen::MatrixXd tempstate;
     Eigen::MatrixXd Q_mat;
     Eigen::MatrixXd R_mat;
     Eigen::MatrixXd ref_mat;
     Eigen::MatrixXd init_mat;
     QMap<int, SwarmAgent *> agentgroup;
     void healthy_plant_stepin();
     void calc_reward();
     double coef_r1;double rp;
     double coef_r2;double rpf;double rf;
signals:
public slots:
     void step_once();
     void matrecieved(Eigen::MatrixXd mat);
};

#endif // MAIN_STREAM_H
