#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <qobject.h>
#include <QOpenGLWidget>
#include <glpainter.h>
#include <QTimer>
class glpainter;
class glwidget: public QOpenGLWidget
{
    Q_OBJECT

public:
    glwidget(QWidget *parent);
    void set_glpainter(glpainter *m_paint);
    void resizeGLwidget(int w,int h);
    void mouseMoveEvent(QMouseEvent *event) override;

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int elapsed;
    glpainter *m_painter;
    int m_width;
    int m_height;

};

#endif // GLWIDGET_H
