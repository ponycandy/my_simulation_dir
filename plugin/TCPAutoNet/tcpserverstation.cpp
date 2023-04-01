#include "tcpserverstation.h"
#include "TCPAutoNetActivator.h"
#include "defines/bit201/CpyDefines.h"
#include "FILE_manage/f_manager.h"
TcpServerStation::TcpServerStation(QObject *parent) : QObject(parent)
{
    server = new QTcpServer();
    agentnum=0;
    //连接信号槽
    connect(server,&QTcpServer::newConnection,this,&TcpServerStation::server_New_Connect);
    Config_All_port();
    //暂时如此，后面使用动态捕捉的方法，其实只要知道所有的可用端口就行，也就是指定一个范围

    //与TCPclient不同，我们不在此处推出信号，因为需要考虑单机上具备多个server和client的情形

}


void TcpServerStation::startlisten(int portnum)
{
    server->listen(QHostAddress::Any, portnum);
}

void TcpServerStation::disconnectport()
{

}

void TcpServerStation::send(QByteArray data,int tcpID)
{
    mclient->write(data);
}

void TcpServerStation::Config_All_port()
{
    QString available_port=f_Read_TXT("./config/available_port.txt");
    int port_sum=f_get_mat_width(available_port);
    for(int i=0;i<port_sum;i++)
    {
    int port=f_get_mat_at(0,i,available_port).toInt();
    startlisten(port);
    }
}

QTcpSocket *TcpServerStation::Getsending_socket(QString IP, int port)
{

    QTcpSocket *socketnow=clients_ID_map.value(IP);
    return socketnow;
}





void TcpServerStation::tcprecieved()
{
    QByteArray buffer = mclient->readAll();
    QByteArray buffer_to_send;
    int n=buffer.size();
    //目标地址存在于数据的里面
    //预想的数据定义：[int ]
    //解析前面的所有header
    BITDefine::NetHeadet header_struct;
    const char* ptData = buffer;
    int offset;

    memcpy((void *)&header_struct.ipv4_phase_1,(void *)(ptData),  4);
    offset =4;
    ptData += offset;

    memcpy((void *)&header_struct.ipv4_phase_2,(void *)(ptData),  4);
    offset =4;
    ptData += offset;

    memcpy((void *)&header_struct.ipv4_phase_3,(void *)(ptData),  4);
    offset =4;
    ptData += offset;

    memcpy((void *)&header_struct.ipv4_phase_4,(void *)(ptData),  4);
    offset =4;
    ptData += offset;

    memcpy((void *)&header_struct.port,(void *)(ptData),  4);
    offset =4;
    ptData += offset;

    memcpy((void *)&header_struct.source_ipv4_phase_1,(void *)(ptData),  4);
    offset =4;
    ptData += offset;

    memcpy((void *)&header_struct.source_ipv4_phase_2,(void *)(ptData),  4);
    offset =4;
    ptData += offset;

    memcpy((void *)&header_struct.source_ipv4_phase_3,(void *)(ptData),  4);
    offset =4;
    ptData += offset;

    memcpy((void *)&header_struct.source_ipv4_phase_4,(void *)(ptData),  4);
    offset =4;
    ptData += offset;

    memcpy((void *)&header_struct.source_port,(void *)(ptData),  4);
    offset =4;
    ptData += offset;

    memcpy(buffer_to_send.data() + 0, buffer.constData() + sizeof (header_struct), n-sizeof (header_struct));


    QString ipv4=QString(header_struct.ipv4_phase_1)+"."+QString(header_struct.ipv4_phase_2)+"."+QString(header_struct.ipv4_phase_3)+"."+QString(header_struct.ipv4_phase_4);
    QTcpSocket *a_socket=Getsending_socket(ipv4,header_struct.port);//IP,port
    a_socket->write(buffer_to_send);

}

void TcpServerStation::server_New_Connect()
{
    QTcpSocket *a_socket;
    a_socket=server->nextPendingConnection();
    connect(a_socket,&QTcpSocket::readyRead,this,&TcpServerStation::tcprecieved);

    QString ipv4= a_socket->peerAddress().toString();
    int portnum=a_socket->peerPort();
    clients_ID_map.insert(ipv4,a_socket);
    agentnum++;

}
