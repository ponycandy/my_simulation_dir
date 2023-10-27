#include "glpainter3d.h"

glpainter3D::glpainter3D(QObject *parent)
{
    QSurfaceFormat format;
    format.setVersion(4, 3);    // 关键是这一句，设置opengl版本号
    QSurfaceFormat::setDefaultFormat(format);

    m_widget=new base_widget;
    m_glwidget=new glwidget3D(m_widget);
    m_glwidget->set_glpainter(this);
    m_widget->setpainter(this);

    m_width=1000;
    m_height=600;
    background.setColor(Qt::black);
    background.setStyle(Qt::SolidPattern);

    factorin=1;
    pixel_per_meter=30;//initial condition
    calc_bounder();
    mousex=0;recorded_mouse_x=0;operation_num=0;
    mousey=0;recorded_mouse_y=0;mouse_is_pressed=0;
    //    resizeWindow(400,300);
    setupUI();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, m_glwidget, &glwidget3D::animate);
}

void glpainter3D::setupUI()
{
    layout = new QGridLayout;
    layout->addWidget(m_glwidget);
    //    layout->setContentsMargins();
    m_widget->setLayout(layout);
    //    m_widget->show();
}

void glpainter3D::get_mouse_pos(int x, int y)
{
    if(mouse_is_pressed==0)
    {
        mousex=x/pixel_per_meter+x_min;
        mousey=y_max-y/pixel_per_meter;
    }
    else
    {
     //   move_the_bound(x/pixel_per_meter+x_min,y_max-y/pixel_per_meter);
        //我们要仔细思考三维场景下的变换公式
        //我们的鼠标移动的始终是视角
    }
}

void glpainter3D::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{

}

void glpainter3D::zoomin()
{

}

void glpainter3D::zoomout()
{

}

void glpainter3D::calc_bounder()
{

}

void glpainter3D::record_pressed_mouse(int x, int y)
{

}
