
#ifndef SWARMSIMSERVICE_H
#define SWARMSIMSERVICE_H

#include <QObject>
#include <QWidget>
#include <service/Animateservice.h>
#include <service/SimDynamicsservice.h>
#include <SwarmAgent.h>
class SwarmSimservice
{
public:
    virtual ~SwarmSimservice(){}
    virtual Animateservice* getwidgetoperator()=0;
    virtual SimDynamicsservice* get_simer()=0;
    virtual SwarmSimservice* cloneservice()=0;
    virtual QMap<int,SwarmAgent*> getagentgroup()=0;
    virtual void startsim()=0;
    virtual void set_neib_sequnce(int flag)=0;
    virtual void init_plant(int steptime,int init_method,SwarmAgent *singleagents)=0;//obs的位置在txt文件中指定

};
#define SwarmSimservice_iid "SwarmSimservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(SwarmSimservice,SwarmSimservice_iid  )
QT_END_NAMESPACE

#endif

