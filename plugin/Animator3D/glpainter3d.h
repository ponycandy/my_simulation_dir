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
class glwidget3D;
class base_widget;
class glpainter3D: public QObject//,public Animateservice，这个移植到osgi框架下再说
{
    Q_OBJECT
public:
    explicit glpainter3D(QObject *parent = nullptr);
    void setupUI();
    void get_mouse_pos(int x, int y);
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    void zoomin();
    void zoomout();
    void calc_bounder();
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

};

#endif // GLPAINTER3D_H
