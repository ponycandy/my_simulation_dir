//UDPmessageservice.h
#ifndef UDPMESSAGESERVICE_H
#define UDPMESSAGESERVICE_H
#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QDebug>

class UDPmessageservice
{
public:
    virtual ~UDPmessageservice(){}
    virtual  bool send(const QByteArray &data, const QHostAddress &destination, quint16 port)=0;
    virtual QByteArray sendAndWaitForReply(const QByteArray data, const QHostAddress &destination, quint16 port)=0;
    virtual bool init(int port, const QString &host = "127.0.0.1")=0;
    virtual void subscribe_callback(QObject *receiver, const char *slot)=0;
    virtual UDPmessageservice* cloneservice()=0;
    virtual void disconnectfromhost()=0;

};
#define UDPmessageservice_iid "UDPmessageservice"
QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(UDPmessageservice,UDPmessageservice_iid  )
QT_END_NAMESPACE
#endif
