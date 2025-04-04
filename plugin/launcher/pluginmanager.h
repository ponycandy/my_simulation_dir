#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include  <QtXml>
#include <QDomDocument>
#include <QString>
#include <QMap>
#include "plugininterface.h"
#include "plugincontext.h"
#include "service/SystemDefaultservice.h"
class pluginmanager : public QObject,SystemDefaultservice
{
    Q_OBJECT
public:
    explicit pluginmanager();
    void readconfigfile(const char* filepath);
    bool loadplugin();
    void startplugin();
    void initplugin();
    void setupevent();
    void ReadXMLFile(const QString sFileName);
    void ShowXMLDoc(QDomElement &docElem);
    void InitCONTEXT();
    void unload_plugin(QString pluginname) override;
    void load_plugin(QString path, QString pluginname) override;
    QStringList getpluginlist() override;
    QStringList getservicelist() override;
    int m_pluginnum;
    QMap<int, QString> m_pluginnamemap;
    QMap<int, PluginInterface*> m_pluginmap;

    PluginContext* P_CONTEXT;

signals:

};

#endif // PLUGINMANAGER_H
