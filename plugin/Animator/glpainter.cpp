#include "glpainter.h"
#include "AnimatorActivator.h"
#include "QPaintEvent"
#include "include/GL_2D/OSGIEVENT.h"
#include "QtDebug"
glpainter::glpainter(QObject *parent) : QObject(parent),m_glwidget(NULL),m_widget(NULL)
{
    QSurfaceFormat format;
    format.setVersion(4, 3);    // 关键是这一句，设置opengl版本号
    QSurfaceFormat::setDefaultFormat(format);

    m_widget=new base_widget;
    m_glwidget=new glwidget(m_widget);
    m_glwidget->set_glpainter(this);
    m_widget->setpainter(this);

    m_width=1000;
    m_height=600;
    background.setColor(Qt::black);
    background.setStyle(Qt::SolidPattern);
    agent_brush.setColor(Qt::red);
    agent_brush.setStyle(Qt::SolidPattern);
    obs_brush.setColor(Qt::blue);
    obs_brush.setStyle(Qt::SolidPattern);
    factorin=1;
    pixel_per_meter=30;//initial condition
    calc_bounder();
    mousex=0;recorded_mouse_x=0;operation_num=0;
    mousey=0;recorded_mouse_y=0;mouse_is_pressed=0;
    //    resizeWindow(400,300);
    setupUI();




    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, m_glwidget, &glwidget::animate);

}

void glpainter::setupUI()
{
    layout = new QGridLayout;
    layout->addWidget(m_glwidget);
    //    layout->setContentsMargins();
    m_widget->setLayout(layout);
    //    m_widget->show();
}
double glpainter::to_pixel_x(double x)
{
    double pix_x=((x-x_min)*pixel_per_meter);
    return  pix_x;
}

double glpainter::to_pixel_y(double y)
{
    double pix_y=((y_max-y)*pixel_per_meter);
    return  pix_y;
}

double glpainter::to_cord_x(double x)
{
    double x_r=x/pixel_per_meter+x_min;
    return x_r;
}

double glpainter::to_cord_y(double y)
{
    double y_r=y_max-y/pixel_per_meter;
    return y_r;
}

double glpainter::to_cord_l(double l)
{
    double length=l/pixel_per_meter;
    return length;
}

void glpainter::record_pressed_mouse(int x, int y)
{
    recorded_mouse_x=to_cord_x(x);
    recorded_mouse_y=to_cord_y(y);
    emit sig_mouse_pressed(recorded_mouse_x,recorded_mouse_y,x,y);
}

double glpainter::to_pixel_l(double l)
{
    double length=l*pixel_per_meter;
    return  length;
}
void glpainter::zoomin()
{
    factorin=1.25;
    x_min=mousex-(mousex-x_min)/factorin;
    x_max=mousex+(x_max-mousex)/factorin;
    pixel_per_meter=m_width/(x_max-x_min);//pixel per meter

    y_min=mousey-(mousey-y_min)/factorin;
    y_max=mousey+(y_max-mousey)/factorin;
    pixel_per_meter=m_height/(y_max-y_min);//pixel per meter
}

void glpainter::register_painter(DrawOperation *painter)
{
    operation_num+=1;
    DrawOperation_map.insert(operation_num,painter);
    painter->m_animator=this;
}

void glpainter::draw_polygon(QPolygonF poly)
{
    int length_0=poly.length();
    QPolygonF draw_F;
    for(int i=0;i<length_0;i++)
    {
        draw_F << QPointF(to_pixel_x(poly.at(i).x()), to_pixel_y(poly.at(i).y()));
    }
    brush_painter->drawPolygon(draw_F);
}

void glpainter::draw_square_oneside(double leftside_center_x, double leftside_center_y, double width, double height, double spinangle)
{
    QPointF points[4] = {
        QPointF(width/2, 0),
        QPointF(-width/2, 0),
        QPointF(-width/2, height),
        QPointF(width/2, height),
    };
    //    qDebug()<<cos(alpha);
    //    qDebug()<<sin(alpha);
    double x_c1;
    double y_c1;
    QPolygonF poly;
    for(int i=0;i<=3;i++)
    {
        x_c1=cos(spinangle)*points[i].x()+sin(spinangle)*points[i].y()+leftside_center_x;
        y_c1=-sin(spinangle)*points[i].x()+cos(spinangle)*points[i].y()+leftside_center_y;
        points[i].setX(x_c1);
        points[i].setY(y_c1);
        poly<<points[i];
    }
    this->draw_polygon(poly);
}

void glpainter::draw_square(double centerx, double centery, double width, double height, double spinangle)
{
    QPointF points[4] = {
        QPointF(width/2, -height/2),
        QPointF(-width/2, -height/2),
        QPointF(-width/2, height/2),
        QPointF(width/2, height/2),
    };
    //    qDebug()<<cos(alpha);
    //    qDebug()<<sin(alpha);
    double x_c1;
    double y_c1;
    QPolygonF poly;
    for(int i=0;i<=3;i++)
    {
        x_c1=cos(spinangle)*points[i].x()+sin(spinangle)*points[i].y()+centerx;
        y_c1=-sin(spinangle)*points[i].x()+cos(spinangle)*points[i].y()+centery;
        points[i].setX(x_c1);
        points[i].setY(y_c1);
        poly<<points[i];
    }
    this->draw_polygon(poly);
}

void glpainter::draw_line(double startx, double starty, double endx, double endy)
{
    double pix_x0=to_pixel_x(startx);
    double pix_y0=to_pixel_y(starty);
    double pix_x1=to_pixel_x(endx);
    double pix_y1=to_pixel_y(endy);
    brush_painter->drawLine(QLineF(pix_x0,pix_y0,pix_x1,pix_y1));
}

void glpainter::draw_spline()
{
    brush_painter->setBrush(Qt::transparent);
    brush_painter->drawPath(*paintpath);

}

void glpainter::draw_beacon(double x, double y, double alpha)
{
    int pixl=15;
    double pix_x=to_pixel_x(x);
    double pix_y=to_pixel_y(y);
    double x_c1=0;
    double y_c1=0;

    QPointF points[5] = {
        QPointF(pixl, 0),
        QPointF(-pixl, -pixl),
        QPointF(0, 0),
        QPointF(-pixl, pixl),
        QPointF(pixl, 0),

    };
    //    qDebug()<<cos(alpha);
    //    qDebug()<<sin(alpha);

    for(int i=0;i<=4;i++)
    {
        x_c1=cos(alpha)*points[i].x()+sin(alpha)*points[i].y()+pix_x;
        y_c1=-sin(alpha)*points[i].x()+cos(alpha)*points[i].y()+pix_y;
        points[i].setX(x_c1);
        points[i].setY(y_c1);
    }


    brush_painter->drawPolygon(points, 5);

}

void glpainter::draw_circle(double x, double y, double r)
{
    double pix_y=to_pixel_y(y);
    double pix_x=to_pixel_x(x);
    double l=to_pixel_l(r);

    brush_painter->drawEllipse(pix_x-l,pix_y-l,2*l,2*l);
}

void glpainter::Add_path_point(double x, double y)
{

    double pix_y=to_pixel_y(y);
    double pix_x=to_pixel_x(x);
     paintpath->lineTo(pix_x,pix_y);

}

void glpainter::Start_a_path(double x, double y)
{
    paintpath=new QPainterPath;
    QPointF point;
    double pix_y=to_pixel_y(y);
    double pix_x=to_pixel_x(x);
    point.setX(pix_x);
    point.setY(pix_y);
    paintpath->moveTo(point);
}


void glpainter::zoomout()
{
    factorin=0.8;
    x_min=mousex-(mousex-x_min)/factorin;
    x_max=mousex+(x_max-mousex)/factorin;
    pixel_per_meter=m_width/(x_max-x_min);//pixel per meter

    y_min=mousey-(mousey-y_min)/factorin;
    y_max=mousey+(y_max-mousey)/factorin;
    pixel_per_meter=m_height/(y_max-y_min);//pixel per meter
}

void glpainter::move_the_bound(double x, double y)
{
    x_min=x_min-(x-mousex);
    x_max=x_max-(x-mousex);
    y_min=y_min-(y-mousey);
    y_max=y_max-(y-mousey);
}
void glpainter::get_mouse_pos(int x, int y)
{
    if(mouse_is_pressed==0)
    {
        mousex=x/pixel_per_meter+x_min;
        mousey=y_max-y/pixel_per_meter;
    }
    else
    {
        move_the_bound(x/pixel_per_meter+x_min,y_max-y/pixel_per_meter);
    }
}
void glpainter::resizeWindow(int width, int height)
{
    m_width=width;
    m_height=height;
    m_widget->resize(m_width,m_height);

    m_glwidget->resizeGLwidget(m_width,m_height);
    calc_bounder();


}

Animateservice *glpainter::cloneservice()
{
    glpainter *servicenew=new glpainter;
    return servicenew;

}

QWidget *glpainter::getwidget()
{
    return m_widget;
}

void glpainter::start_animate()
{
    timer->start(10);
}

void glpainter::stop_animate()
{
    timer->stop();
}

void glpainter::calc_bounder()
{
    x_max=m_width/(2*pixel_per_meter);
    x_min=-x_max;
    y_max=m_height/(2*pixel_per_meter);
    y_min=-y_max;
}
void glpainter::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    brush_painter=painter;
    painter->setBrush(background);
    painter->fillRect(event->rect(), background);
    for(int i=1;i<=operation_num;i++)
    {
        DrawOperation_map.value(i)->draw();
    }
}
