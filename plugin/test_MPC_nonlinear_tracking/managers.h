
#ifndef MANAGERS_H
#define MANAGERS_H


#include <QObject>
#include "service/SimDynamicsservice.h"
#include "service/MPC_Trackerservice.h"
#include "twotwoode.h"
class managers : public QObject
{
    Q_OBJECT
public:
    explicit managers(QObject *parent = nullptr);
    SimDynamicsservice *m_service;
    MPC_Trackerservice *mpc;
    twotwoode *odef;
signals:

};

#endif // MANAGERS_H
