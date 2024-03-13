#include "hronslider.h"

HronSlider::HronSlider(QWidget *parent)
    : QWidget{parent}
{
    valueNow=2.5;
    unit=1;
    unitlength_pic=12;

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    resize(110,400);
}

void HronSlider::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(Qt::green));
    QRectF rect(45,height()/2-30, 60, 18);
    painter.drawRect(rect);
    QFont font;
    font.setPointSize(12); // Replace 12 with the desired font size
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignHCenter, QString::number(valueNow, 'f', 2));

    painter.setPen(QPen(Qt::black,1));

    painter.drawLine(40,height()/2,60,height()/2);

    double lowerClosest = (static_cast<int>(valueNow / unit)) * unit;
    double higherClosest = lowerClosest + unit;
    int gridnum= (static_cast<int>(lowerClosest / unit));
    int tempgridnum=gridnum;

    double posinit_lower=height()/2+(valueNow-lowerClosest)/unit*unitlength_pic;
    double posinit_higher=posinit_lower-unitlength_pic;

    painter.setPen(QPen(Qt::green,1));//设置画笔形式
    while(posinit_lower<height())
    {
        double length=0;
        if(gridnum%5==0)
        {
            length=20;
            font.setPointSize(8); // Replace 12 with the desired font size
            painter.setFont(font);
            painter.drawText(0,posinit_lower, QString::number(gridnum*unit, 'f', 1));
        }
        else
        {
            length=10;
        }
        painter.drawLine(40-length,posinit_lower,40,posinit_lower);//画直线

        posinit_lower+=unitlength_pic;
        gridnum-=1;
    }
    gridnum=tempgridnum+1;
    painter.setPen(QPen(Qt::green,1));//设置画笔形式
    while(posinit_higher>0)
    {
        double length=0;
        if(gridnum%5==0)
        {
            length=20;
            font.setPointSize(8); // Replace 12 with the desired font size
            painter.setFont(font);
            painter.drawText(0,posinit_higher, QString::number(gridnum*unit, 'f', 1));
        }
        else
        {
            length=10;
        }
        painter.drawLine(40-length,posinit_higher,40,posinit_higher);

        posinit_higher-=unitlength_pic;
        gridnum+=1;
    }
    painter.setPen(QPen(Qt::green,3));
    painter.drawLine(40,0,40,height());
}

void HronSlider::updateSliderValue(double value)
{
    valueNow=value;
    update();
}

void HronSlider::setunit(double unit_value, int unitleng)
{
    unit=unit_value;
    unitlength_pic=unitleng;
}
