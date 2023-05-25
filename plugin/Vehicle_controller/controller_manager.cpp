
#include "controller_manager.h"

controller_manager::controller_manager(QObject *parent)
    : QObject{parent}
{
    m_controller=new controller;
}

