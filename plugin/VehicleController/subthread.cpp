#include "subthread.h"
#include "vehicle1_communicationActivator.h"
#include "QtDebug"
#include <QElapsedTimer>
#include <QCoreApplication>
#include <defines/Vehicle1_data.h>
subthread::subthread(QObject *parent):m_service(NULL)
{
    client=new QMQTT::Client;
    m_service=vehicle1_communicationActivator::getService<vehicle_1_1Datamanageservice>("vehicle_1_1Datamanageservice");
    connect(client,SIGNAL(connected()),this,SLOT(onConnected()));
    //connect(client,SIGNAL(subscribed(QString)),this,SLOT(onSubscribed(QString)));
    connect(client,SIGNAL(received(QMQTT::Message)),this,SLOT(onReceived(QMQTT::Message)));
    m_service_ros=vehicle1_communicationActivator::getService<vehicle_1_rosservice>("vehicle_1_rosservice");
}


void subthread::slot_start_node()
{
    client->connectToHost();


}

void subthread::slot_stop_node()
{
    client->disconnectFromHost();

}

void subthread::slot_setNet(XTLevent event)
{
    QString plos_sk=event.m_dict.value("cilentID(R)").toString();
    char* plos=plos_sk.toLatin1().data();
    char *plo=new char[64];
    memset(plo,0x00,64);
    memcpy(plo,plos,plos_sk.length());

    QString plos_sk1=event.m_dict.value("port(R)").toString();
    char* plos1=plos_sk1.toLatin1().data();
    char *plo1=new char[64];
    memset(plo1,0x00,64);
    memcpy(plo1,plos1, plos_sk1.length());

    QString plos_sk2=event.m_dict.value("host(R)").toString();
    char* plos2=plos_sk2.toLatin1().data();
    char *plo2=new char[64];
    memset(plo2,0x00,64);
    memcpy(plo2,plos2,plos_sk2.length());

    QString plos_sk3=event.m_dict.value("username(R)").toString();
    char* plos3=plos_sk3.toLatin1().data();
    char *plo3=new char[64];
    memset(plo3,0x00,64);
    memcpy(plo3,plos3,plos_sk3.length());

    QString plos_sk4=event.m_dict.value("password(R)").toString();
    char* plos4=plos_sk4.toLatin1().data();
    char *plo4=new char[64];
    memset(plo4,0x00,64);
    memcpy(plo4,plos4,plos_sk4.length());

    QString plos_sk5=event.m_dict.value("topicname(R)").toString();
    char* plos5=plos_sk5.toLatin1().data();
    char *plo5=new char[64];
    memset(plo5,0x00,64);
    memcpy(plo5,plos5,plos_sk5.length());

    client->setHost(QHostAddress(plo2));
    client->setClientId(plo);
    client->setUsername(plo3);
    client->setPassword(plo4);
    topicname=plo5;

}

void subthread::onConnected()
{
    client->subscribe(topicname, 0);
}

void subthread::onReceived(const QMQTT::Message &message)
{
    QByteArray mine_data=message.payload();
    int size=message.payload().size();
    quint8* ptCache=(quint8*)mine_data.data();
    if((ptCache[0]==0xcc) && (ptCache[1]==0xaa))
    {
        QSharedPointer<V1DATA::POINTCLOUD> m_cloud_ptr;
        m_cloud_ptr = QSharedPointer<V1DATA::POINTCLOUD>(new V1DATA::POINTCLOUD);

        parse((const char*)mine_data,*(m_cloud_ptr.data()));
        V1DATA::SHARED_POINTCLOUD m_cloud_ptr_pass;
        m_cloud_ptr_pass.SH_POINTCLOUD=m_cloud_ptr;
        m_service_ros->pub(m_cloud_ptr_pass);
        //do not use qshared pointer it will not delete
        //problem:should not use service?(though will be slower)
    }
    if((ptCache[0]==0xee) && (ptCache[1]==0xaa))
    {
        QSharedPointer<V1DATA::POINTCLOUD> m_cloud_ptr;
        m_cloud_ptr = QSharedPointer<V1DATA::POINTCLOUD>(new V1DATA::POINTCLOUD);

        parse((const char*)mine_data,*(m_cloud_ptr.data()));
        V1DATA::SHARED_POINTCLOUD m_cloud_ptr_pass;
        m_cloud_ptr_pass.SH_POINTCLOUD=m_cloud_ptr;
        m_service_ros->pub(m_cloud_ptr_pass);
        //do not use qshared pointer it will not delete
        //problem:should not use service?(though will be slower)
    }
}

void subthread::parse(const char *data, V1DATA::POINTCLOUD &PTtopic)
{
        const char* ptData = data;
        int offset;

        memcpy((void *)&PTtopic.header,(void *)(ptData),  2);
        offset =2;
        ptData += offset;

        memcpy((void *)&PTtopic.secquense,(void *)(ptData),  4);
        offset =4;
        ptData += offset;

        memcpy((void *)&PTtopic.time,(void *)(ptData),  sizeof(V1DATA::ROSTIMESTAMP));
        offset =sizeof(V1DATA::ROSTIMESTAMP);
        ptData += offset;

        memcpy((void *)&PTtopic.pointnum,(void *)(ptData),  4);
        offset =4;
        ptData += offset;

        offset=sizeof (V1DATA::SINGEPOINTDATA);
        for(int i=0;i<PTtopic.pointnum;i++)
        {
            V1DATA::SINGEPOINTDATA  m_point_s;
            memcpy((void *)&m_point_s,(void *)(ptData),  sizeof (V1DATA::SINGEPOINTDATA));
            ptData += offset;
            PTtopic.point_group.append(m_point_s);
        }
}
