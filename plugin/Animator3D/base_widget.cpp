#include "base_widget.h"
#include "ui_base_widget.h"

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

void base_widget::setpainter(glpainter3D *m_paint)
{
    m_painter=m_paint;
}

void base_widget::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y()>0)
    {
        m_painter->movein();
    }
    else
    {
        m_painter->moveout();

    }
}

void base_widget::mousePressEvent(QMouseEvent *event)
{
//    m_painter->record_pressed_mouse(event->x(),event->y());
    m_painter->mouse_is_pressed=1;

}

void base_widget::mouseReleaseEvent(QMouseEvent *event)
{
    m_painter->mouse_is_pressed=0;
}

void base_widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)
    {
        m_painter->moveup();
    }
    else if(event->key() == Qt::Key_Down)
    {
        m_painter->movedown();
    }
    else if(event->key() == Qt::Key_Left)
    {
        m_painter->moveleft();

    }
    else if(event->key() == Qt::Key_Right)
    {
        m_painter->moveright();

    }
    else
    {

    }
}
