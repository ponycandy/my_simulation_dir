#ifndef SIMMANAGER_H
#define SIMMANAGER_H

#include <QObject>
#include "vehicle.h"
#include "xmlcore.h"
#include "service/SimDynamicsservice.h"
#include "service/Tcpcommunicateservice.h"
#include "service/CPYcoderservice.h"
#include "mypainter.h"
class simmanager : public QObject
{
    Q_OBJECT
public:
    explicit simmanager(QObject *parent = nullptr);
    void matrecieved(Eigen::MatrixXd mat);
    //这里只当作普通的仿真器来用
    vehicle *singleone;
    SimDynamicsservice *dysim;
    Tcpcommunicateservice *TCPsoc;
    CPYcoderservice *decoder;
    int agentnum;
     QMap<int, SwarmAgent *> agentgroup;
    MYpainter *m_painter;

signals:

};

#endif // SIMMANAGER_H
