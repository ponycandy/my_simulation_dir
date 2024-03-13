#include "customslider.h"

CustomSlider::CustomSlider(QWidget *parent)
    : QWidget{parent}
{
    valueNow=2.5;
    unit=1;
    unitlength_pic=12;

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    resize(400,60);

}

void CustomSlider::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(Qt::green));
    QRectF rect(width()/2+15,42, 60, 30);
    painter.drawRect(rect);

    QFont font;
    font.setPointSize(12); // Replace 12 with the desired font size
    painter.setFont(font);

    painter.drawText(rect, Qt::AlignHCenter, QString::number(valueNow, 'f', 2));

    painter.setPen(QPen(Qt::black,1));//设置画笔形式

    painter.drawLine(width()/2,60,width()/2,60-18);//画直线

    double lowerClosest = (static_cast<int>(valueNow / unit)) * unit;
    double higherClosest = lowerClosest + unit;
    int gridnum= (static_cast<int>(lowerClosest / unit));
    int tempgridnum=gridnum;

    double posinit_lower=width()/2-(valueNow-lowerClosest)/unit*unitlength_pic;
    double posinit_higher=posinit_lower+unitlength_pic;

    painter.setPen(QPen(Qt::green,1));//设置画笔形式
    while(posinit_lower>0)
    {
        double length=0;
        if(gridnum%5==0)
        {
            length=20;
            font.setPointSize(8);
            painter.setFont(font);
            painter.drawText(posinit_lower, 20, QString::number(gridnum*unit, 'f', 1));
        }
        else
        {
            length=10;
        }
        painter.drawLine(posinit_lower,40,posinit_lower,40-length);//画直线

        posinit_lower-=unitlength_pic;
        gridnum-=1;
    }
    gridnum=tempgridnum+1;
    painter.setPen(QPen(Qt::green,1));//设置画笔形式
    while(posinit_higher<width())
    {
        double length=0;
        if(gridnum%5==0)
        {
            length=20;
            font.setPointSize(8);
            painter.setFont(font);
            painter.drawText(posinit_higher, 20, QString::number(gridnum*unit, 'f', 1));
        }
        else
        {
            length=10;
        }
        painter.drawLine(posinit_higher,40,posinit_higher,40-length);

        posinit_higher+=unitlength_pic;
        gridnum+=1;
    }
    painter.setPen(QPen(Qt::green,3));
    painter.drawLine(0,40,width(),40);

}

void CustomSlider::updateSliderValue(double value)
{
    valueNow=value;
    update();
}

void CustomSlider::setunit(double unit_value, int unitleng)
{
    unit=unit_value;
    unitlength_pic=unitleng;
}
