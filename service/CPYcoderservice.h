
#ifndef CPYCODERSERVICE_H
#define CPYCODERSERVICE_H

#include <QObject>
#include <Eigen/Core>
#include <service/Tcpcommunicateservice.h>
#include <service/TCPserverservice.h>
class CPYcoderservice
{
public:
    virtual ~CPYcoderservice(){}
    virtual void sendMAT(Eigen::MatrixXd mat,Tcpcommunicateservice * usingservice)=0;
    virtual void sendMAT(Eigen::MatrixXd &mat,TCPserverservice * usingservice)=0;
     virtual void sendMAT(Eigen::MatrixXd &mat)=0;
    virtual CPYcoderservice* cloneservice()=0;
    virtual void Bind_Slot(QObject *reciever,const char *method)=0;
    virtual void getmat(QByteArray data)=0;
    virtual void Server_mode_connect(int portnum)=0;
    virtual void Client_mode_connect(QString IP,int portnum)=0;
};
#define CPYcoderservice_iid "CPYcoderservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(CPYcoderservice,CPYcoderservice_iid  )
QT_END_NAMESPACE

#endif

