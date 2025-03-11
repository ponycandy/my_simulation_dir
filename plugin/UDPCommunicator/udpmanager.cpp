#include "udpmanager.h"

UDPmanager::UDPmanager(QObject *parent) : QObject(parent)
{

}

bool UDPmanager::init(int port, const QString &host)
{
    QMutexLocker locker(&mutex);

    socket = new QUdpSocket(this);

    // 绑定端口
    if (!socket->bind(QHostAddress(host), port)) {
        qDebug() << "Failed to bind UDP socket:" << socket->errorString();
        return false;
    }

    connect(socket, &QUdpSocket::readyRead, this, &UDPmanager::processPendingDatagrams);
    qDebug() << "UDP service initialized on host" << host << "port" << port;
    return true;
}

bool UDPmanager::send(const QByteArray &data, const QHostAddress &destination, quint16 port)
{
    QMutexLocker locker(&mutex);

    if (!socket) {
        qDebug() << "UDP socket not initialized.";
        return false;
    }

    qint64 bytesWritten = socket->writeDatagram(data, destination, port);
    if (bytesWritten == -1) {
        qDebug() << "Failed to send datagram:" << socket->errorString();
        return false;
    }

    qDebug() << "Datagram sent to" << destination.toString() << ":" << port;
    return true;
}

void UDPmanager::subscribe_callback(QObject *receiver, const char *slot)
{
    QMutexLocker locker(&mutex);

    if (!socket) {
        qDebug() << "UDP socket not initialized.";
        return;
    }

    // 连接信号到外部的回调槽
    connect(this,SIGNAL(newDatagramReceived(QByteArray)),receiver,slot);

}

void UDPmanager::disconnectfromhost()
{

    // 断开当前套接字
    if (socket) {
        // 断开信号连接
        disconnect(socket, &QUdpSocket::readyRead, this, &UDPmanager::processPendingDatagrams);
        // 关闭套接字
        socket->close();
        // 删除套接字对象
        delete socket;
        socket = nullptr;
    }

}

UDPmessageservice *UDPmanager::cloneservice()
{
    UDPmanager *newservice=new UDPmanager;
    return newservice;
}
