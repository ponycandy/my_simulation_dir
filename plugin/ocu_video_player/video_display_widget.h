#ifndef VIDEO_DISPLAY_WIDGET_H
#define VIDEO_DISPLAY_WIDGET_H

#include <QWidget>
#include <QPainter>

#include <QSlider>
#include <batterystatus.h>
#include <hronslider.h>
#include <customslider.h>
#include <directionhron.h>
#include <crossaxle.h>
class video_display_widget : public QWidget
{
    Q_OBJECT

public:
    explicit video_display_widget(QWidget *parent = nullptr);
    ~video_display_widget();

    QSlider *slider;
    HronSlider *customvslider;
    BatteryStatus *battery;
    CustomSlider *customhslider;
    DirectionHron *direct;
    crossaxle *cross;
    QString pathname;
    int mode;
    int vid_x,vid_y,vid_width,vid_height;

public slots:


    void slotOnStart();
    void slotOnStop();
    void on_horizontalSlider_valueChanged(int value);
private:

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.fillRect(rect(), Qt::transparent);
    }



};

#endif // VIDEO_DISPLAY_WIDGET_H
