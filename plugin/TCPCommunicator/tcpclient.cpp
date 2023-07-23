#include "tcpclient.h"
#include "TCPCommunicatorActivator.h"
#include "OSGIEVENT.h"

TCPClient::TCPClient(QObject *parent) : QObject(parent),mclient(NULL)
{
    mclient=new QTcpSocket;
    connect(mclient,&QTcpSocket::readyRead,this,&TCPClient::tcprecieved);
    TCPCommunicatorActivator::publishsignal(this,SIGNAL(hexrecieved(QByteArray))
                                            ,OSGIEVENT::TCPHEXRECIEVED,Qt::QueuedConnection);
}
void TCPClient::Bind_Slot(QObject *reciever, const char *method)
{
    connect(this,SIGNAL(hexrecieved(QByteArray)),reciever,method);
}

void TCPClient::connectport()
{
    if(mclient->state() != QAbstractSocket::ConnectedState)
    {
        //连接服务器
        mclient->connectToHost(IP,portnum);
        //等待连接成功
        if(!mclient->waitForConnected(-1))
        {
            qDebug() << "Connection failed!";
            return;
        }
        qDebug() << "Connection success!";
    }

}

void TCPClient::disconnectport()
{
    if(mclient->state() == QAbstractSocket::ConnectedState)
    {
        mclient->disconnectFromHost();
        qDebug() << "已断开";
    }
}

void TCPClient::send(QByteArray data)
{

    if(mclient->state() == QAbstractSocket::ConnectedState)
    {
        //发送数据
        mclient->write(data);

    }
}

void TCPClient::send(QString data)
{
    QByteArray byteArr = data.toUtf8();
    send(byteArr);
}

void TCPClient::setport(QString port, QString ip)
{
    IP=ip;
    portnum=port.toInt();
}

void TCPClient::send_decorated(QByteArray data, QString IP0, int port)
{
//    BITDefine::NetHeadet headerfor;
//    headerfor.port=port;
//    headerfor.source_port=portnum;
//    headerfor.ipv4_phase_1= f_get_text_between(IP0,"",".").toUInt();
//    headerfor.ipv4_phase_2= f_get_text_between(IP0,".",".").toUInt();

//    headerfor.ipv4_phase_3= f_get_text_between(IP0,".",".").toUInt();

//    headerfor.ipv4_phase_4= f_get_text_between(IP0,".","").toUInt();

//    headerfor.source_ipv4_phase_1= f_get_text_between(IP,"",".").toUInt();
//    headerfor.source_ipv4_phase_2= f_get_text_between(IP,".",".").toUInt();

//    headerfor.source_ipv4_phase_3= f_get_text_between(IP,".",".").toUInt();

//    headerfor.source_ipv4_phase_4= f_get_text_between(IP,".","").toUInt();


//    QByteArray data_to_send;
//    memcpy(data_to_send.data() + 0, (void *)&headerfor, sizeof (headerfor));
//    memcpy(data_to_send.data() + sizeof (headerfor),data.data()+0, data.size());

//    if(mclient->state() == QAbstractSocket::ConnectedState)
//    {
//        //发送数据
//        mclient->write(data);

//    }
}


Tcpcommunicateservice *TCPClient::cloneservice()
{
    TCPClient *newservice=new TCPClient;
    return newservice;
}

void TCPClient::tcprecieved()
{
    QByteArray buffer = mclient->readAll();
    emit hexrecieved(buffer);
}
