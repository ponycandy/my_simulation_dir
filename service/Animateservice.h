
#ifndef ANIMATESERVICE_H
#define ANIMATESERVICE_H

#include <QObject>
#include <include/GL_2D/draw_operation.h>
#include <QPainter>
class DrawOperation;
class Animateservice
{
public:
    virtual ~Animateservice(){}
    virtual void resizeWindow(int width,int height)=0;
    virtual void start_animate()=0;
    virtual void stop_animate()=0;
    virtual void register_painter(DrawOperation *painter)=0;
    virtual void draw_polygon(QPolygonF poly)=0;
    virtual void draw_beacon(double x, double y, double alpha)=0;
    virtual void draw_circle(double x,double y,double r)=0;
    virtual void draw_line(double startx,double starty,double endx,double endy)=0;
    virtual void draw_square(double centerx,double centery,double width,double height,double spinangle)=0;
    virtual void draw_square_oneside(double leftside_center_x,double leftside_center_y,double width,double height,double spinangle)=0;

    virtual Animateservice* cloneservice()=0;
    virtual QWidget* getwidget()=0;
    QPainter *brush_painter;

};
#define Animateservice_iid "Animateservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(Animateservice,Animateservice_iid  )
QT_END_NAMESPACE

#endif

