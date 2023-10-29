#ifndef GLPAINTER3D_H
#define GLPAINTER3D_H

#pragma once

#include "glwidget3d.h"
#include <QObject>
#include <QPainter>
#include "QPaintEvent"
#include "base_widget.h"
#include <QTimer>
#include "QGridLayout"
#include "service/Animateservice3Dservice.h"
class glwidget3D;
class base_widget;
class glpainter3D: public QObject,public Animateservice3Dservice//，这个移植到osgi框架下再说
{
    Q_OBJECT
public:
    explicit glpainter3D(QObject *parent = nullptr);
    void setupUI();
    void get_mouse_pos(int x, int y);
    void drawcube(float Dx,float Dy,float Dz,
                  float centerx,float centery,float centerz,
                  float alpha,float beta,float gama) override;
    void resizeWindow(int width,int height) override;
    void start_animate() override;
    void stop_animate() override;
    void register_painter(Drawer3D *painter) override;
    Animateservice3Dservice* cloneservice() override;
    QWidget *getwidget() override;
    void paint();
    void zoomin();
    void zoomout();
    void calc_bounder();
    void moveup();
    void movedown();
    void moveright();
    void moveleft();
    void movein();
    void moveout();
    void rotateCams(int x,int y);
    void record_pressed_mouse(int x,int y);
    base_widget *m_widget;
    glwidget3D *m_glwidget;
    QTimer *timer;
    QGridLayout *layout;
    QBrush background;

    int mousex;
    int mousey;
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
    int m_width;
    int operation_num;
    int m_height;

    QMap<int,Drawer3D*>    DrawOperation_map;


};

#endif // GLPAINTER3D_H
