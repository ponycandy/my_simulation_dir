#ifndef SWARM_ETM_H
#define SWARM_ETM_H
#ifndef QTPLUGIN_H
#define QTPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include "plugininterface.h"
#include "service/eventservice.h"

#include "simmanager.h"

class swarm_ETMActivator : public QObject,public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
    Q_PLUGIN_METADATA(IID PluginInterface_iid)
public:
    explicit swarm_ETMActivator(QObject *parent = nullptr);
    void stop() override;
    void start() override;
    void init(PluginContext *CONTEXT) override;
    static void postevent(XTLevent  event)
    {
        m_CONTEXT->postevent(event);
    }
    static void subscribeslot(QObject *reciever, const char *method, QString eventname,Qt::ConnectionType type)
    {
        m_CONTEXT->subscribeslot(reciever, method, eventname,type);
    }
    static void publishsignal(QObject *sender, const char *signal, QString eventname,Qt::ConnectionType type)
    {
        m_CONTEXT->publishsignal(sender, signal, eventname,type);
    }
    static void registerservice(QObject* service,QString name)
    {
    m_CONTEXT->registerservice(service,name);
    }
    static void subscribevent(QString name,EventService *handle)
    {
    m_CONTEXT->subscribeslot(name,handle);
    }
    template <typename T>
    static T* getService(QString servicename)
    {

        QObject *servicehandle=m_CONTEXT->getservice(servicename);
        return dynamic_cast<T*>(servicehandle);
    }


private:
    static swarm_ETMActivator *m_instance;
    static PluginContext *m_CONTEXT;
    simmanager *m_manager;
};

#endif 
#endif
