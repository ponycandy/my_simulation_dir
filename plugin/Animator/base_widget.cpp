
#include "base_widget.h"
#include "ui_base_widget.h"
#include "QWheelEvent"
base_widget::base_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::base_widget)
{
    ui->setupUi(this);
    this->resize(1000,600);
}

base_widget::~base_widget()
{
    delete ui;
}

void base_widget::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y()>0)
    {
        m_painter->zoomin();
    }
    else
    {
        m_painter->zoomout();

    }
}

void base_widget::mousePressEvent(QMouseEvent *event)
{
    m_painter->record_pressed_mouse(event->x(),event->y());
    m_painter->mouse_is_pressed=1;

}

void base_widget::mouseReleaseEvent(QMouseEvent *event)
{
    m_painter->mouse_is_pressed=0;
}

void base_widget::setpainter(glpainter *m_paint)
{
    m_painter=m_paint;
}
