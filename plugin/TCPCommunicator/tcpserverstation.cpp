﻿#include "tcpserverstation.h"
#include "defines/bit201/CpyDefines.h"
#include "FILE_manage/f_manager.h"
TcpServerStation::TcpServerStation(QObject *parent) : QObject(parent)
{
    server = new QTcpServer();
    agentnum=0;
    //连接信号槽
    connect(server,&QTcpServer::newConnection,this,&TcpServerStation::server_New_Connect);
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

void TcpServerStation::send(QByteArray data)
{
    mclient->write(data);

}

void TcpServerStation::Bind_Slot(QObject *reciever, const char *method)
{
    connect(this,SIGNAL(hexrecieved(QByteArray)),reciever,method);
}

TCPserverservice *TcpServerStation::cloneservice()
{
    TcpServerStation *newservice=new TcpServerStation;
    return newservice;
}






void TcpServerStation::tcprecieved()
{
    QByteArray buffer = mclient->readAll();

    //触发本插件的hexrecieved信号
    //本插件提供一个服务，用来直接连接hexrecieved信号和槽函数

    emit hexrecieved(buffer);
}

void TcpServerStation::server_New_Connect()
{
    mclient=server->nextPendingConnection();
    connect(mclient,&QTcpSocket::readyRead,this,&TcpServerStation::tcprecieved);

}
