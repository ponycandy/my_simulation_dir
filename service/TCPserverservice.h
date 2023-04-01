
#ifndef TCPSERVERSERVICE_H
#define TCPSERVERSERVICE_H

#include <QObject>
class TCPserverservice
{
public:
    virtual ~TCPserverservice(){}
    virtual void startlisten(int portnum)=0;
    virtual void disconnectport()=0;
    virtual void send(QByteArray data)=0;
    virtual void Bind_Slot(QObject *reciever,const char *method)=0;
    virtual TCPserverservice* cloneservice()=0;

};
#define TCPserverservice_iid "TCPserverservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(TCPserverservice,TCPserverservice_iid  )
QT_END_NAMESPACE

#endif

