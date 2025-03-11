#ifndef UDPMANAGER_H
#define UDPMANAGER_H

#include <QObject>
#include <service/UDPmessageservice.h>
class UDPmanager : public QObject,public UDPmessageservice
{
    Q_OBJECT
public:
    explicit UDPmanager(QObject *parent = nullptr);
    bool init(int port, const QString &host = "127.0.0.1") override;
    bool send(const QByteArray &data, const QHostAddress &destination, quint16 port) override;
    void subscribe_callback(QObject *receiver, const char *slot) override;
    void disconnectfromhost() override;
    UDPmessageservice* cloneservice() override;
signals:
    void newDatagramReceived(const QByteArray &data);
private slots:
    void processPendingDatagrams()
    {
        while (socket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(socket->pendingDatagramSize());
            socket->readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);

            // 发出信号，通知订阅者
            emit newDatagramReceived(datagram);
        }
    }
private:
    QUdpSocket *socket = nullptr;
    QHostAddress senderAddress;
    quint16 senderPort;
    mutable QMutex mutex;
};

#endif // UDPMANAGER_H
