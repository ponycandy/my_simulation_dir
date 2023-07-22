#include "dataloggermanager.h"
#include "DataLoggerActivator.h"


DataloggerManager::DataloggerManager(QObject *parent)
    : QObject{parent}
{
    Tcpcommunicateservice *tcpservice=DataLoggerActivator::getService<Tcpcommunicateservice>("Tcpcommunicateservice");
    m_serivce=tcpservice->cloneservice();
    DataLoggerActivator::registerservice(this,"Datalogservice");
}

void DataloggerManager::log(QString word, int level)
{
    short Id=0;
    if(level==0)//记录
    {
        Id=0xaabb;
    }
    if(level==1)//打印
    {
        Id=0xaac;
    }
    if(level==2)//打印而且记录
    {
        Id=0xaadd;
    }
    std::string data2send=spdgcreatePacket(word.toStdString(),Id);
    QByteArray data2=QByteArray::fromStdString(data2send);
    m_serivce->send(data2);
    return;

}

void DataloggerManager::createlogfile(QString logfilename, int port)
{
    QString command=QString("start ./logs/SPDG_logger.exe ")+QString::number(port)+" "+logfilename;
    //    system(command.toStdString().c_str());
    m_serivce->setport(QString::number(port),"127.0.0.1");
    m_serivce->connectport();
    portname.push_back(m_serivce);
}

std::string DataloggerManager::spdgcreatePacket(const std::string &message, short Id)
{
    // Create a header instance
    spdlogheader frameHeader;
    frameHeader.sequence= 0xaaaa;
    frameHeader.Id = Id;
    frameHeader.length = message.length();

    // Convert the frame header to a binary string
    std::string headerStr(reinterpret_cast<const char*>(&frameHeader), sizeof(spdlogheader));

    // Concatenate the header and the message
    std::string packet = headerStr + message;

    return packet;
}
