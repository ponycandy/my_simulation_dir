#ifndef INTERFACEMANAGER_H
#define INTERFACEMANAGER_H

#include <QObject>
#include <service/Animateservice.h>
#include <confisetter.h>
class InterfaceManager : public QObject
{
    Q_OBJECT
public:
    explicit InterfaceManager(QObject *parent = nullptr);
    Animateservice *Aservice;
    confiSetter *conf;
signals:

};

#endif // INTERFACEMANAGER_H
