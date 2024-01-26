
#ifndef OCU_CAR_CORESERVICE_H
#define OCU_CAR_CORESERVICE_H

#include <QObject>
#include "defines/OcuDefines.h"

class ocu_car_coreservice
{
public:
    virtual ~ocu_car_coreservice(){}
    virtual void setConnectStatus(bool connectStatus)=0;
    virtual void setControlStatus(bool controlStatus)=0;
    virtual void addView(UcsDefines::UcsViewKind viewKind, QWidget *view) = 0;
    virtual void changeView(UcsDefines::UcsViewKind viewKind) = 0;
    virtual UcsDefines::UcsViewKind getCurrentView() = 0;
    virtual void changeMenu(const QString &oldMenu, const QString &newMenu, const QString &text) = 0;
    virtual void changeMenu(const int num,const QString &newMenu,const QString &text) = 0;

};
#define ocu_car_coreservice_iid "ocu_car_coreservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(ocu_car_coreservice,ocu_car_coreservice_iid  )
QT_END_NAMESPACE

#endif

