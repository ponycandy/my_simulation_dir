#include "crossaxle.h"

crossaxle::crossaxle(QWidget *parent)
    : QWidget{parent}
{

     resize(50,50);
}

void crossaxle::paintEvent(QPaintEvent *event)
{
    QBrush obs_brush;
    QColor col(0,255,0,125);
    obs_brush.setColor(col);
    obs_brush.setStyle(Qt::SolidPattern);

    QPen pen(Qt::transparent); // Create a transparent pen

    QPainter painter(this);
    painter.setPen(pen); // Set the transparent pen

    painter.setBrush(obs_brush);
    painter.drawRect(width()/2, 0, 3, height());
    painter.drawRect(0,height()/2,  width(), 3);

}
