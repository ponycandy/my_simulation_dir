
#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H


#include <QObject>
#include "controller.h"

class controller_manager : public QObject
{
    Q_OBJECT
public:
    explicit controller_manager(QObject *parent = nullptr);
    controller *m_controller;
signals:

};

#endif // CONTROLLER_MANAGER_H
