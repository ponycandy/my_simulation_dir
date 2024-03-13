#ifndef ANIMATOR_MANAGER_H
#define ANIMATOR_MANAGER_H
#include "myanimator.h"
#include <QWidget>
#include "controlwidget.h"
class animator_manager
{
public:
    animator_manager();
    Animateservice *m_service;
    MyAnimator *m_painter;
    QWidget *anim_wid;
    ControlWidget *controller;
};

#endif // ANIMATOR_MANAGER_H
