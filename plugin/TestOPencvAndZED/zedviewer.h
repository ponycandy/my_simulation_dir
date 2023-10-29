#ifndef ZEDVIEWER_H
#define ZEDVIEWER_H

#include "service/Animateservice3Dservice.h"
#include "QWidget"
//#include "cubedrawer.h"
#include "pointclouddrawer.h"
#include "testcuda.h"

class ZEDviewer
{
public:
    ZEDviewer();

    Animateservice3Dservice *m_anim;
    QWidget *Mwidget;
  //  cubedrawer *m_painter;
  //  PointClouddrawer *cloudpainter;
    TestCuda *m_cuda;
};

#endif // ZEDVIEWER_H
