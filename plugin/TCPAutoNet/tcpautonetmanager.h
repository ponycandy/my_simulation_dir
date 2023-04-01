#ifndef TCPAUTONETMANAGER_H
#define TCPAUTONETMANAGER_H
#include <QObject>
#include <service/TcpAutoNetservice.h>
#include <tcpserverstation.h>
class TCPAutoNetManager:public QObject
{
    Q_OBJECT
public:
    TCPAutoNetManager();
    TcpServerStation *m_service;
};

#endif // TCPAUTONETMANAGER_H
