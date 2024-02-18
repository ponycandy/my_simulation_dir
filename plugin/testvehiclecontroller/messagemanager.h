#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <QObject>
#include "service/VehicleControlservice.h"
#include "controllerwidget.h"
class messagemanager : public QObject
{
    Q_OBJECT
public:
    explicit messagemanager(QObject *parent = nullptr);
    VehicleControlservice *m_service;
    controllerwidget *m_wid;
signals:
private slots:
    void nowsendone();
};

#endif // MESSAGEMANAGER_H
