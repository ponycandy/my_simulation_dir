#ifndef GLPAINTER_H
#define GLPAINTER_H

#include <QObject>
#include "glwidget.h"
#include "base_widget.h"
#include "service/Animateservice.h"
#include <QTimer>
#include "QGridLayout"
#include <QPainter>
#include <include/GL_2D/draw_operation.h>
#include <QPainterPath>
#include <QMap>
class glwidget;
class base_widget;
class glpainter : public QObject,public Animateservice
{
    Q_OBJECT
public:
    explicit glpainter(QObject *parent = nullptr);
    void setupUI();
    void zoomin();
    void register_painter(DrawOperation* painter);
    void draw_polygon(QPolygonF poly) override;
    void draw_square_oneside(double leftside_center_x, double leftside_center_y, double width, double height, double spinangle) override;
    void draw_square(double centerx,double centery,double width,double height,double spinangle) override;
    void draw_line(double startx, double starty, double endx, double endy) override;
    void draw_spline() override;
    void draw_beacon(double x, double y, double alpha) override;
    void draw_circle(double x, double y, double r) override;
    void Add_path_point(double x,double y) override;
    void Start_a_path(double x,double y) override;

    void zoomout();
    void move_the_bound(double x,double y);
    void resizeWindow(int width, int height) override;
    Animateservice* cloneservice() override;
    QWidget * getwidget() override;
    void start_animate() override;
    void stop_animate() override;
    void calc_bounder();
    double to_pixel_x(double x);
    double to_pixel_y(double y);
    double to_pixel_l(double l);
    double to_cord_x(double x);
    double to_cord_y(double y);
    double to_cord_l(double l);
    void record_pressed_mouse(int x,int y);


    void get_mouse_pos(int x, int y);
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    base_widget *m_widget;
    glwidget *m_glwidget;

    QTimer *timer;
    QGridLayout *layout;
    int m_width;
    int m_height;

    QBrush background;
    QBrush agent_brush;
    QBrush obs_brush;
    QBrush circleBrush;

    QFont textFont;
    QPen circlePen;
    QPen textPen;

    double mousex;
    double mousey;
    double recorded_mouse_x;
    double recorded_mouse_y;

    double factorin;
    double pixel_per_meter;
    double x_min;
    double y_min;
    double x_max;
    double y_max;
    double close_x=0;
    double close_y=0;
    int mouse_is_pressed;

    QMap<int,DrawOperation*>    DrawOperation_map;
    int operation_num;
    QPainterPath *paintpath;
signals:
    void sig_mouse_pressed(double x,double y,double pix_x,double pix_y);

};

#endif // GLPAINTER_H
