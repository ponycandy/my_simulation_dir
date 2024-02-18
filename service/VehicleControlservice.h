
#ifndef VEHICLECONTROLSERVICE_H
#define VEHICLECONTROLSERVICE_H

#include <QObject>
#include <QByteArray>
class VehicleControlservice
{
public:
    virtual ~VehicleControlservice(){}
    virtual void send(QByteArray byteArray,QString vehicle,QString topicname)=0;
    virtual VehicleControlservice* cloneservice()=0;

};
#define VehicleControlservice_iid "VehicleControlservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(VehicleControlservice,VehicleControlservice_iid  )
QT_END_NAMESPACE

#endif

