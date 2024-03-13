#include "directionhron.h"

DirectionHron::DirectionHron(QWidget *parent)
    : QWidget{parent}
{
    directions.push_back("N");
    directions.push_back("E");
    directions.push_back("S");
    directions.push_back("W");

    valueNow=50;
    double width=200;
    unitlength_pic=150;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    resize(width,60);
}

void DirectionHron::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(Qt::green));
    double angle=normalizeAngle(valueNow);
    unit=90;

    double lowerClosest = (static_cast<int>(valueNow / unit)) * unit;
    double higherClosest = lowerClosest + unit;
    int gridnum= (static_cast<int>(lowerClosest / unit))+16;
    int tempgridnum=gridnum;

    double posinit_lower=width()/2-(valueNow-lowerClosest)/unit*unitlength_pic;
    double posinit_higher=posinit_lower+unitlength_pic;
    QFont font("Arial", 10);
    painter.setFont(font);
    painter.setPen(QPen(Qt::green,3));
    if(gridnum<0)
    {
        gridnum=gridnum+4;
    }
    while(posinit_lower>0)
    {

        QString di=directions[gridnum%4];
        painter.drawText(posinit_lower-3, 10,di );
        painter.drawLine(posinit_lower,20,posinit_lower,40);//画直线
        posinit_lower-=unitlength_pic;
        gridnum-=1;
    }

    gridnum=tempgridnum+1;
    if(gridnum<0)
    {
        gridnum=gridnum+4;
    }
    painter.setPen(QPen(Qt::green,3));
    while(posinit_higher<width())
    {

        QString di=directions[gridnum%4];
        painter.drawText(posinit_higher-3, 10,di);
        painter.drawLine(posinit_higher,20,posinit_higher,40);
        posinit_higher+=unitlength_pic;
        gridnum+=1;
    }
    painter.drawLine(0,40,width(),40);

}

double DirectionHron::normalizeAngle(double angle)
{
    while (angle > 180) {
        angle -= 360;
    }
    while (angle < -180) {
        angle += 360;
    }
    return angle;
}

void DirectionHron::updateSliderValue(double value)
{
    valueNow=value;
    update();
}

void DirectionHron::setunit(double unit_value, int unitleng)
{

}
