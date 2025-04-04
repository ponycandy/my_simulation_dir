//AIinterfaceservice.h
#ifndef AIINTERFACESERVICE_H
#define AIINTERFACESERVICE_H
#include <QObject>
#include <iostream>
#include <map>
#include <functional>
#include <aiinterface/variable_Interface.h>
#include <QVector>
using Handler = std::function<void(const QVector<JsonVar*>& j)>;
class AIinterfaceservice
{
public:
    virtual ~AIinterfaceservice(){}
    virtual void register_function(QString name, Handler handler)=0;
    virtual void register_variable(QString name, JsonVar* var)=0;
    virtual void set_variable(QString parentname,json j)=0;
    virtual void call_function(QString funcname,QVector<JsonVar*> input)=0;

};
#define AIinterfaceservice_iid "AIinterfaceservice"
QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(AIinterfaceservice,AIinterfaceservice_iid  )
QT_END_NAMESPACE
#endif
