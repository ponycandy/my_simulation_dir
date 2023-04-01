#ifndef TCPSERVERSTATION_H
#define TCPSERVERSTATION_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <service/TCPserverservice.h>
#include <defines/bit201/CpyDefines.h>
class TcpServerStation : public QObject,public TCPserverservice
{
    Q_OBJECT
public:
    explicit TcpServerStation(QObject *parent = nullptr);
    void startlisten(int portnum) ;
    void disconnectport() ;
    void send(QByteArray data) ;
    void Bind_Slot(QObject *reciever, const char *method) override;
    TCPserverservice * cloneservice() override;
    QString IP;
    int portnum;
    uint32_t agentnum;
    QTcpServer *server ;
    QTcpSocket *mclient;
    QTcpSocket *Getsending_socket(QString IP,int port);
    QMap<QString,QTcpSocket*> clients_ID_map;
    QMap<QString,uint32_t> clients_IP_map;
    QMap<uint32_t ,int> clients_Port_map;
//按照顺序给与每一个连接以固定IP，允许外部程序更改这个IP
signals:
    void hexrecieved(QByteArray data);

public slots:
    void tcprecieved();
    void server_New_Connect();
};

#endif // TCPSERVERSTATION_H
