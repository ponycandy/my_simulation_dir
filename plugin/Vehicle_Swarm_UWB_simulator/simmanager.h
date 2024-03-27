#ifndef SIMMANAGER_H
#define SIMMANAGER_H

#include <QObject>
#include "mypainter.h"
#include "vehicle.h"
#include "service/SwarmSimservice.h"
#include "service/SimDynamicsservice.h"
#include "startwindow.h"
class simmanager : public QObject
{
    Q_OBJECT
public:
    explicit simmanager(QObject *parent = nullptr);
    int intercounts;
    MYpainter *m_painter;
    vehicle *singleone;
    SimDynamicsservice* dysim;
    QMap<int,SwarmAgent*> agentgroup;
    bool choosenow_flag=false;
    startwindow *m_start;
    int agentnum;
signals:
    void update_target(double x,double y);
public slots:
    void dysimslotstart();
    void slot_choose_bool(bool choosenow);
    void slot_mouse_pressed(double x,double y,double pix_x,double pix_y);

};

#endif // SIMMANAGER_H
