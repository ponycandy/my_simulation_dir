#include "tcpmanager.h"
#include "TCPCommunicatorActivator.h"
tcpmanager::tcpmanager(QObject *parent) : QObject(parent),m_client(NULL)
{
    m_client=new TCPClient;
    m_client_1=new TcpServerStation;
    TCPCommunicatorActivator::registerservice(m_client,"Tcpcommunicateservice");
    TCPCommunicatorActivator::registerservice(m_client_1,"TCPserverservice");

//使用一个TCPAutoNet插件实现多个server和多个client的槽函数触发
}
