#ifndef BASE_WIDGET_H
#define BASE_WIDGET_H

#include <QWidget>
#include "glpainter.h"
class glpainter;
namespace Ui {
class base_widget;
}

class base_widget : public QWidget
{
    Q_OBJECT

public:
    explicit base_widget(QWidget *parent = nullptr);
    ~base_widget();
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void setpainter(glpainter *m_paint);
private:
    Ui::base_widget *ui;
    glpainter *m_painter;
};

#endif // BASE_WIDGET_H
