#include "graphing.h"
#include "TestPolyPaintingActivator.h"
#include "xmlcore.h"
graphing::graphing(QObject *parent)
    : QObject{parent}
{
    m_service=TestPolyPaintingActivator::getService<Animateservice>("Animateservice");
    m_visual=new visualize;
    m_widget=m_service->getwidget();
    m_widget->show();
    m_service->register_painter(m_visual);
    m_service->start_animate();

}
