//SystemDefaultservice.h
#ifndef SYSTEMDEFAULTSERVICE_H
#define SYSTEMDEFAULTSERVICE_H
#include <QObject>
class SystemDefaultservice
{
public:
    virtual ~SystemDefaultservice(){}
    virtual void load_plugin(QString path,QString pluginname)=0;
    virtual void unload_plugin(QString pluginname)=0;
    virtual QStringList getpluginlist()=0;
    virtual QStringList getservicelist()=0;
};
#define SystemDefaultservice_iid "SystemDefaultservice"
QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(SystemDefaultservice,SystemDefaultservice_iid  )
QT_END_NAMESPACE
#endif
