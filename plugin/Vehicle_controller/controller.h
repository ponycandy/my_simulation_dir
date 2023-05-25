
#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QObject>
#include "service/VehicleControlservice.h"

class controller : public QObject,public VehicleControlservice
{
    Q_OBJECT
public:
    explicit controller(QObject *parent = nullptr);

signals:

};

#endif // CONTROLLER_H
