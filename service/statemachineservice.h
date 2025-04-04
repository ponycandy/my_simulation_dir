//statemachineservice.h
#ifndef STATEMACHINESERVICE_H
#define STATEMACHINESERVICE_H
#include <QObject>
class statemachineservice
{
public:
    virtual ~statemachineservice(){}
    virtual statemachineservice* cloneservice()=0;
};
#define statemachineservice_iid "statemachineservice"
QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(statemachineservice,statemachineservice_iid  )
QT_END_NAMESPACE
#endif
