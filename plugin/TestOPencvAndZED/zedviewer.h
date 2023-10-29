#ifndef ZEDVIEWER_H
#define ZEDVIEWER_H

#include "service/Animateservice3Dservice.h"
#include "QWidget"
#include "cubedrawer.h"
class ZEDviewer
{
public:
    ZEDviewer();

    Animateservice3Dservice *m_anim;
    QWidget *Mwidget;
    cubedrawer *m_painter;
};

#endif // ZEDVIEWER_H
