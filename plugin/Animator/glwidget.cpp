#include "glwidget.h"

#include "QPainter"
#include "QMouseEvent"
glwidget::glwidget(QWidget *parent)
{
    setMouseTracking(true);
    elapsed = 0;
    m_width=1000;//默认大小
    m_height=600;
//    setFixedSize(m_width, m_height);
    setAutoFillBackground(false);

}

void glwidget::set_glpainter(glpainter *m_paint)
{
    m_painter=m_paint;
    //    m_painter->set_size(m_width,m_height);
}

void glwidget::resizeGLwidget(int w, int h)
{
   resize(w,h);
   m_width=w;
   m_height=h;
}

void glwidget::mouseMoveEvent(QMouseEvent *event)
{
    m_painter->get_mouse_pos(event->x(),event->y());
}



void glwidget::animate()
{
    update();
}

void glwidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    m_painter->paint(&painter, event, 0);
    painter.end();
}
