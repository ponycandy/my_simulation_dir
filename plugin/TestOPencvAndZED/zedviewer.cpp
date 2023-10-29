#include "zedviewer.h"
#include "TestOPencvAndZEDActivator.h"
ZEDviewer::ZEDviewer()
{
    m_painter=new cubedrawer;
    m_anim=TestOPencvAndZEDActivator::getService<Animateservice3Dservice>("Animateservice3Dservice");
    m_anim->register_painter(m_painter);
    Mwidget=m_anim->getwidget();
    Mwidget->show();
    m_anim->start_animate();
}
