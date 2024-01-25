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
    client_S=new QMQTT::Client;
    client_R=new QMQTT::Client;
    setNet(client_S,cilentID_S,port_S,host_S,username_S,password_S,topicname_S);
    setNet(client_R,cilentID_R,port_R,host_R,username_R,password_R,topicname_R);

    connect(client_R,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(client_R,SIGNAL(received(QMQTT::Message)),this,SLOT(onReceived(QMQTT::Message)));


}

void SingleVehicleCard::setNet(QMQTT::Client *client, QString cilentID, QString port, QString host, QString username, QString password, QString topicname)
{
    client->setHost(QHostAddress(host));
    client->setClientId(cilentID);
    client->setUsername(username);
    client->setPassword(QByteArray::fromStdString(password.toStdString()));

}

void SingleVehicleCard::send(QByteArray data)
{
    QMQTT::Message message;
    message.setId(0);
    message.setQos(0);
    message.setTopic(topicname_S);
    message.setPayload(data);
    client_S->publish(message);
}

void SingleVehicleCard::disconnect()
{
    client_S->disconnectFromHost();
    client_R->disconnectFromHost();
}

void SingleVehicleCard::connectall()
{
    client_S->connectToHost();
    client_R->connectToHost();
}

void SingleVehicleCard::onConnected()
{
    client_R->subscribe(topicname_R,0);
}

void SingleVehicleCard::onReceived(const QMQTT::Message &message)
{
    QByteArray mine_data=message.payload();
    int size=message.payload().size();
    quint8* ptCache=(quint8*)mine_data.data();
    if((ptCache[0]==0xcc) && (ptCache[1]==0xaa))//点云数据，暂时对windows关闭
    {
#ifdef __linux__
        QSharedPointer<V1DATA::POINTCLOUD> m_cloud_ptr;
        m_cloud_ptr = QSharedPointer<V1DATA::POINTCLOUD>(new V1DATA::POINTCLOUD);

        parse((const char*)mine_data,*(m_cloud_ptr.data()));
        V1DATA::SHARED_POINTCLOUD m_cloud_ptr_pass;
        m_cloud_ptr_pass.SH_POINTCLOUD=m_cloud_ptr;
        m_service_ros->pub(m_cloud_ptr_pass);
        //do not use qshared pointer it will not delete
        //problem:should not use service?(though will be slower)
#endif
    }
    if((ptCache[0]==0xee) && (ptCache[1]==0xaa))
    {

    }
}
