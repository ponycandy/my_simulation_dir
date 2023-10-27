#ifndef BASE_WIDGET_H
#define BASE_WIDGET_H
#pragma once

#include <QWidget>
#include "glpainter3d.h"
class glpainter3D;
namespace Ui {
class base_widget;
}

class base_widget : public QWidget
{
    Q_OBJECT

public:
    explicit base_widget(QWidget *parent = nullptr);
    ~base_widget();

    void setpainter(glpainter3D *m_paint);
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::base_widget *ui;
    glpainter3D *m_painter;
};

#endif // BASE_WIDGET_H
