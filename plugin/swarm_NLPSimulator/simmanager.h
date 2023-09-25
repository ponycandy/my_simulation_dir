#ifndef SIMMANAGER_H
#define SIMMANAGER_H

#include <QObject>
#include "vehicle.h"
#include "xmlcore.h"
#include "service/SimDynamicsservice.h"
#include "service/Tcpcommunicateservice.h"
#include "service/CPYcoderservice.h"
#include "mypainter.h"
#include "startwindow.h"
class simmanager : public QObject
{
    Q_OBJECT
public:
    explicit simmanager(QObject *parent = nullptr);
    vehicle *singleone;
    int intercounts;
    SimDynamicsservice *dysim;
    Tcpcommunicateservice *TCPsoc;
    CPYcoderservice *decoder;
    int agentnum;
    QMap<int, SwarmAgent *> agentgroup;
    MYpainter *m_painter;
    startwindow *m_start;
public slots:
    void slotstart();
    void returncount();
};

#endif // SIMMANAGER_H
