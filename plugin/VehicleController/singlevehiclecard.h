#ifndef SINGLEVEHICLECARD_H
#define SINGLEVEHICLECARD_H

#include <QObject>
#include "qmqtt.h"
class SingleVehicleCard : public QObject
{
    Q_OBJECT
public:
    explicit SingleVehicleCard(QObject *parent = nullptr);
    void setupconnection();
    void disconnect();
    void connectall();
    void initialization();
    void setNet(QMQTT::Client *client,QString cilentID,
                QString port,QString host,QString username,QString password,
                QString topicname);
    int vehiclenumber;
    QString vehiclename;
    QString videoAddress;
    QString cilentID_S;
    QString host_S;
    QString port_S;
    QString topicname_S;
    QString username_S;
    QString password_S;

    QString cilentID_R;
    QString host_R;
    QString port_R;
    QString topicname_R;
    QString username_R;
    QString password_R;
    QMQTT::Client *client_S;
    QMQTT::Client *client_R;

signals:

private slots:
    void send(QByteArray data);

    void onConnected();
    void onReceived(const QMQTT::Message& message);
};

#endif // SINGLEVEHICLECARD_H
