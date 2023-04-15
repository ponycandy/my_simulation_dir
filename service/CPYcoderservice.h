
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
    virtual void sendMAT(Eigen::MatrixXd mat,TCPserverservice * usingservice)=0;
};
#define CPYcoderservice_iid "CPYcoderservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(CPYcoderservice,CPYcoderservice_iid  )
QT_END_NAMESPACE

#endif

