#include "AnimatorActivator.h"
#include "include/GL_2D/OSGIEVENT.h"


AnimatorActivator* AnimatorActivator::m_instance=Q_NULLPTR;
PluginContext* AnimatorActivator::m_CONTEXT=Q_NULLPTR;
AnimatorActivator::AnimatorActivator(QObject *parent) : QObject(parent),m_painter(NULL)
{
    m_instance=this;
}
void AnimatorActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void AnimatorActivator::start()
{
    if(m_painter == NULL)
    {
        m_painter = new glpainter;
        AnimatorActivator::registerservice(m_painter,"Animateservice");

    }
}
void AnimatorActivator::stop()
{
delete this;

}
