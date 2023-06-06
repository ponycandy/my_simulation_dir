
#ifndef VEHICLECONTROLSERVICE_H
#define VEHICLECONTROLSERVICE_H

#include <QObject>
#include <Eigen/Core>
class VehicleControlservice
{
public:
    virtual ~VehicleControlservice(){}
    virtual Eigen::MatrixXd feedback(Eigen::MatrixXd state,
    Eigen::MatrixXd reference)=0;

};
#define VehicleControlservice_iid "VehicleControlservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(VehicleControlservice,VehicleControlservice_iid  )
QT_END_NAMESPACE

#endif

