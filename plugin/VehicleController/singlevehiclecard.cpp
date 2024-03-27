#include "singlevehiclecard.h"

SingleVehicleCard::SingleVehicleCard(QObject *parent)
    : QObject{parent}
{
}

void SingleVehicleCard::setupconnection()
{
    initialization();
}


void SingleVehicleCard::initialization()
{


    //试验一下能不能连上
    client=new QMQTT::Client;
    setNet(client,cilentID_S,port_S,host_S,username_S,password_S);

    connect(client,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(client,SIGNAL(received(QMQTT::Message)),this,SLOT(onReceived(QMQTT::Message)));
}

void SingleVehicleCard::setNet(QMQTT::Client *client, QString cilentID, QString port, QString host, QString username, QString password)
{
    client->setHost(QHostAddress(host));
    client->setClientId(cilentID);
    client->setUsername(username);
    client->setPassword(QByteArray::fromStdString(password.toStdString()));

}

void SingleVehicleCard::send(QByteArray data, QString topic_name)
{
    QMQTT::Message message;
    message.setId(0);
    message.setQos(0);
    message.setTopic(topic_name);
    message.setPayload(data);
    client->publish(message);
}

void SingleVehicleCard::disconnect()
{
    client->disconnectFromHost();
}

void SingleVehicleCard::connectall()
{
    client->connectToHost();
}

void SingleVehicleCard::onConnected()
{
    //here is all,it is not represent by xml config file!
    client->subscribe((vehiclename+"/location"),0);
    client->subscribe((vehiclename+"/matrix"),0);
    client->subscribe((vehiclename+"/pointcloud"),0);
    client->subscribe((vehiclename+"/stringcommandcallback"),0);

    //这里就不用配置文件写了，直接手写,因为onReceived肯定是要写代码的，这里没必要预留可变性
}

void SingleVehicleCard::onReceived(const QMQTT::Message &message)
{
    std::string data(message.payload().constData(), message.payload().length());
    QString topic_name=message.topic();
    if(topic_name==(vehiclename+"/location"))//example:   Songling_1/location
    {
     // 这个再接入到仿真器中,然后做实车
        jetson::VehiclePos status=Autodeserialization<jetson::VehiclePos>(data);
    }
    if(topic_name==(vehiclename+"/matrix"))
    {
        // jetson::mat status=Autodeserialization<jetson::mat>(data);

    }
    if(topic_name==(vehiclename+"/pointcloud"))
    {
//left as hollow
    }
}
