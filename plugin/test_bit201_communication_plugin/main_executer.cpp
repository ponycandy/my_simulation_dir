#include "main_executer.h"
#include "test_bit201_communication_pluginActivator.h"
main_executer::main_executer(QObject *parent) : QObject(parent)
{
    m_widget=new startwidget;
    m_widget->show();


}
