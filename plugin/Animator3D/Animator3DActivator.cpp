#include "Animator3DActivator.h"


Animator3DActivator* Animator3DActivator::m_instance=Q_NULLPTR;
PluginContext* Animator3DActivator::m_CONTEXT=Q_NULLPTR;
Animator3DActivator::Animator3DActivator(QObject *parent) : QObject(parent)
{
    m_instance=this;
}
void Animator3DActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void Animator3DActivator::start()
{
    m_painter=new glpainter3D;
    Animator3DActivator::registerservice(m_painter,"Animateservice3Dservice");
    //下面两行是测试代码
//    m_painter->m_widget->show();
//    m_painter->timer->start(10);
}
void Animator3DActivator::stop()
{
    delete this;

}
