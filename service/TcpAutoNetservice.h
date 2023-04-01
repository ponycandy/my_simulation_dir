
#ifndef TCPAUTONETSERVICE_H
#define TCPAUTONETSERVICE_H

#include <QObject>
class TcpAutoNetservice
{
public:
    virtual ~TcpAutoNetservice(){}
    virtual void Initialize(QString configfile)=0;
    virtual int getID(QString IP);
    virtual void Register_Recieve_SLOT(int Target_ID,QString Function);
    //现需要service内部对ID进行管理

};
#define TcpAutoNetservice_iid "TcpAutoNetservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(TcpAutoNetservice,TcpAutoNetservice_iid  )
QT_END_NAMESPACE

#endif

