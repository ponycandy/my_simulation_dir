#include "zedviewer.h"
#include "TestOPencvAndZEDActivator.h"
ZEDviewer::ZEDviewer()
{
   // m_painter=new cubedrawer;
   // cloudpainter=new PointClouddrawer;
   m_cuda=new TestCuda;
    m_anim=TestOPencvAndZEDActivator::getService<Animateservice3Dservice>("Animateservice3Dservice");
  //  m_anim->register_painter(m_painter);
   // m_anim->register_painter(cloudpainter);
    m_anim->register_painter(m_cuda);
    Mwidget=m_anim->getwidget();
    Mwidget->show();
    m_anim->start_animate();
}
