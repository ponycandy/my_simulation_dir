#include "animator_manager.h"
#include "Visualizer_201Activator.h"
animator_manager::animator_manager()
{
    m_painter=new MyAnimator;
    controller=new ControlWidget;
    m_service=Visualizer_201Activator::getService<Animateservice>("Animateservice");
    m_service->register_painter(m_painter);
    anim_wid=m_service->getwidget();
    controller->set_backgroundPannel(anim_wid);
    controller->startanimate();
    //接下来做界面，通讯就再说
  //  m_service->start_animate();
}
