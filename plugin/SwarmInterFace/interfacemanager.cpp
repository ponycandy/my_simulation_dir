#include "interfacemanager.h"
#include <SwarmInterFaceActivator.h>
InterfaceManager::InterfaceManager(QObject *parent) : QObject(parent)
{
    //首先同一思想，基于Animator进行二次开发
    //可能需要向Animator里面添加更多的事件响应接口
    Aservice=SwarmInterFaceActivator::getService<Animateservice>("Animateservice");
    Aservice=Aservice->cloneservice();
    //注册绘图服务,记下来需要调用绘图的接口



    //新窗口用来指定系统设定

}
