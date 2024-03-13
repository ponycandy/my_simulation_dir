#include "batterystatus.h"

BatteryStatus::BatteryStatus(QWidget *parent)
    : QWidget{parent}
{
    valueNow=0.3;
    resize(140,40);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    // setWindowOpacity(0.5);
}

void BatteryStatus::paintEvent(QPaintEvent *event)
{
    QBrush obs_brush;
    QColor col(0,255,0,125);
    obs_brush.setColor(col);
    obs_brush.setStyle(Qt::SolidPattern);

    QPainter painter(this);
    painter.setPen(QPen(Qt::green,3));
    QRectF rect_1(0,15, 3, 10);
    painter.drawRect(rect_1);

    QRectF rect_2(3,0, 100, 40);
    painter.drawRect(rect_2);

   //

    painter.setPen(QPen(Qt::green,3));//设置画笔形式

   // painter.drawText(rect, Qt::AlignHCenter, QString::number(valueNow, 'f', 2));

    painter.drawText(105, 20, QString::number(100*valueNow, 'f', 0)+"%");

    painter.setBrush(obs_brush);
    QRectF rect_3(103-100*valueNow,0, 100*valueNow, 40);
    painter.drawRect(rect_3);
}

void BatteryStatus::updateSliderValue(double value)
{
    if(value>1)
    {
        value=1;
    }
    if(value<0)
    {
        value=0;
    }
    valueNow=value;
    update();
}
