#include "dataloggermanager.h"
#include "DataLoggerActivator.h"
#include "QDebug"
#include <QFile>
DataloggerManager::DataloggerManager(QObject *parent)
    : QObject{parent}
{
    Tcpcommunicateservice *tcpservice=DataLoggerActivator::getService<Tcpcommunicateservice>("Tcpcommunicateservice");
    m_serivce=tcpservice->cloneservice();

    flag=0;
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

void DataloggerManager::log(int rows, int colums, double value)
{
    short Id=0xaaff;
    QString msg=" "+QString::number(rows)+" "+QString::number(colums)+" "+QString::number(value)+" ";
    std::string data2send=spdgcreatePacket(msg.toStdString(),Id);
    QByteArray data2=QByteArray::fromStdString(data2send);
    m_serivce->send(data2);
    return;
}

void DataloggerManager::createlogfile(QString logfilename, int port)
{
    QString command=QString("start ./logs/SPDG_logger.exe ")+QString::number(port)+" "+logfilename;
    system(command.toStdString().c_str());
    m_serivce->setport(QString::number(port),"127.0.0.1");
    m_serivce->connectport();
    portname.push_back(m_serivce);
    flag=1;
}

void DataloggerManager::createxlsfile(QString logfilename)
{
    customAssert(flag==1,"must create logfile before create xls!");
    short Id=0xaaee;
    std::string data2send=spdgcreatePacket(logfilename.toStdString(),Id);
    QByteArray data2=QByteArray::fromStdString(data2send);
    m_serivce->send(data2);
    return;
}

void DataloggerManager::DeleteFile(QString fileName)
{

    QFile file(fileName);
    if (file.exists()) { // Check if the file exists before deleting
        if (file.remove()) {
            qDebug() << "File removed successfully";
        } else {
            qDebug() << "Failed to remove file";
        }
    } else {
        qDebug() << "File not found";
    }
}

void DataloggerManager::savexlsfile()
{
    //确保至少写入一个数字，否则将会无法保存！！
    short Id=0xbbaa;
    std::string data2send=spdgcreatePacket(" ",Id);
    QByteArray data2=QByteArray::fromStdString(data2send);
    m_serivce->send(data2);
    return;
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

void DataloggerManager::customAssert(bool condition, const char *message)
{
    if (!condition)
    {
        qDebug() << "Assertion Failed: " << message ;
        // Additional print statements or error handling can be added here
        abort(); // Terminate the program
    }
}

Datalogservice *DataloggerManager::cloneservice()
{
    DataloggerManager *newservice=new DataloggerManager;
    return newservice;
}
