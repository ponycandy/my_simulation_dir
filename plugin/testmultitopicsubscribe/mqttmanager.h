#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <QObject>
#include "qmqtt.h"

class mqttmanager : public QObject
{
    Q_OBJECT
public:
    explicit mqttmanager(QObject *parent = nullptr);
    QMQTT::Client *client;

signals:
private slots:
    void onConnected();
    void onReceived(const QMQTT::Message &message);
};

#endif // MQTTMANAGER_H
