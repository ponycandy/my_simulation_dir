#include "mqttmanager.h"

mqttmanager::mqttmanager(QObject *parent)
    : QObject{parent}
{

    client=new QMQTT::Client;
    connect(client,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(client,SIGNAL(received(QMQTT::Message)),this,SLOT(onReceived(QMQTT::Message)));

    client->setHost(QHostAddress("192.168.1.65"));
    client->setClientId("testmultisub");
    client->setUsername("userme");
    client->setPassword(QByteArray::fromStdString("public"));
    client->connectToHost();
}

void mqttmanager::onConnected()
{
    client->subscribe("test_topic_1",0);
    client->subscribe("test_topic_2",0);

}

void mqttmanager::onReceived(const QMQTT::Message &message)
{
    QByteArray mine_data=message.payload();
    QString topicname=message.topic();
    if(topicname=="test_topic_1")
    {
        qDebug()<<topicname;
        qDebug()<<mine_data;
        return;
    }
    if(topicname=="test_topic_2")
    {
        qDebug()<<topicname;
        qDebug()<<mine_data;
        return;
    }
}
