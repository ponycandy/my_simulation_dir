#include "animator_manager.h"
#include "Visualizer_201Activator.h"
animator_manager::animator_manager()
{
    map_service=Visualizer_201Activator::getService<MapService>("MapService");
    mapwidget=map_service->getMapwidget();
    mapwidget->showFullScreen();
    m_control=new ControlWidget;
    m_control->show();
    m_control->M_map=map_service;
}
