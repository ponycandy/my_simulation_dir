#include "DataLoggerActivator.h"


DataLoggerActivator* DataLoggerActivator::m_instance=Q_NULLPTR;
PluginContext* DataLoggerActivator::m_CONTEXT=Q_NULLPTR;
DataLoggerActivator::DataLoggerActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void DataLoggerActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void DataLoggerActivator::start()
{
    m_logger=new DataloggerManager;
    DataLoggerActivator::registerservice(m_logger,"Datalogservice");
}
void DataLoggerActivator::stop()
{
delete this;

}
