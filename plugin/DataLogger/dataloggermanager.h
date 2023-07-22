#ifndef DATALOGGERMANAGER_H
#define DATALOGGERMANAGER_H

#include <QObject>
#include <service/Datalogservice.h>
#include <service/Tcpcommunicateservice.h>

struct spdlogheader {
    short sequence;
    short Id;
    short length;
};
class DataloggerManager : public QObject,public Datalogservice
{
    Q_OBJECT
public:
    explicit DataloggerManager(QObject *parent = nullptr);
    void log(QString word,int level) override;
    void log(int rows,int colums,double value) override;
    void createlogfile(QString logfilename,int port) override;
    void createxlsfile(QString logfilename) override;
    void savexlsfile() override;
    std::string spdgcreatePacket(const std::string& message, short Id);
    void customAssert(bool condition, const char* message);

    Datalogservice* cloneservice() override;
    Tcpcommunicateservice *m_serivce;
    QVector<Tcpcommunicateservice *> portname;

    //调用启动文件，包括链接端口和log文件名

private:
    int flag;
};

#endif // DATALOGGERMANAGER_H
