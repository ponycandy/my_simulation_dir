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
    setNet(client_S,cilentID_S,port_S,host_S,username_S,password_S,topicname_S);
    setNet(client_R,cilentID_R,port_R,host_R,username_R,password_R,topicname_R);

    connect(client_R,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(client_R,SIGNAL(received(QMQTT::Message)),this,SLOT(onReceived(QMQTT::Message)));


}

void SingleVehicleCard::setNet(QMQTT::Client *client, QString cilentID, QString port, QString host, QString username, QString password, QString topicname)
{
    client=new QMQTT::Client;
    QString plos_sk=cilentID;
    char* plos=plos_sk.toLatin1().data();
    char *plo=new char[64];
    memset(plo,0x00,64);
    memcpy(plo,plos,plos_sk.length());

    QString plos_sk1=port;
    char* plos1=plos_sk1.toLatin1().data();
    char *plo1=new char[64];
    memset(plo1,0x00,64);
    memcpy(plo1,plos1, plos_sk1.length());

    QString plos_sk2=host;
    char* plos2=plos_sk2.toLatin1().data();
    char *plo2=new char[64];
    memset(plo2,0x00,64);
    memcpy(plo2,plos2,plos_sk2.length());

    QString plos_sk3=username;
    char* plos3=plos_sk3.toLatin1().data();
    char *plo3=new char[64];
    memset(plo3,0x00,64);
    memcpy(plo3,plos3,plos_sk3.length());

    QString plos_sk4=password;
    char* plos4=plos_sk4.toLatin1().data();
    char *plo4=new char[64];
    memset(plo4,0x00,64);
    memcpy(plo4,plos4,plos_sk4.length());

    QString plos_sk5=topicname;
    char* plos5=plos_sk5.toLatin1().data();
    char *plo5=new char[64];
    memset(plo5,0x00,64);
    memcpy(plo5,plos5,plos_sk5.length());

    client->setHost(QHostAddress(plo2));
    client->setClientId(plos_sk);
    client->setUsername(plos_sk3);
    client->setPassword(plo4);

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
