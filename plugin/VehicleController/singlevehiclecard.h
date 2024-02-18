#ifndef SINGLEVEHICLECARD_H
#define SINGLEVEHICLECARD_H

#include <QObject>
#include "qmqtt.h"
#include "Mqttmessenger/Mqttmessenger.h"
#include "jetsonnanoDATA/jetsonnanoDATA.h"
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
                QString port,QString host,QString username,QString password);
    void send(QByteArray data,QString topic_name);
    int vehiclenumber;
    QString vehiclename;
    QString videoAddress;
    QString cilentID_S;
    QString host_S;
    QString port_S;
    QString username_S;
    QString password_S;
    QMQTT::Client *client;

signals:

private slots:


    void onConnected();
    void onReceived(const QMQTT::Message& message);
};

#endif // SINGLEVEHICLECARD_H
