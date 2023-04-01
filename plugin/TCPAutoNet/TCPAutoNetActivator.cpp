#include "TCPAutoNetActivator.h"


TCPAutoNetActivator* TCPAutoNetActivator::m_instance=Q_NULLPTR;
PluginContext* TCPAutoNetActivator::m_CONTEXT=Q_NULLPTR;
TCPAutoNetActivator::TCPAutoNetActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void TCPAutoNetActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void TCPAutoNetActivator::start()
{
    m_manager=new TCPAutoNetManager;
}
void TCPAutoNetActivator::stop()
{
delete this;

}
