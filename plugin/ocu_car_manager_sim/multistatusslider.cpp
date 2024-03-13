#include "multistatusslider.h"
#include <qpainter.h>
multistatusSlider::multistatusSlider(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

void multistatusSlider::init(QVector<QString> list)
{
    savedvector=list;
    innerslider=new QSlider(this);
    innerslider->setMaximum(list.length()-1);
    connect(innerslider,SIGNAL(sliderMoved(int)),this,SLOT(on_Slider_valueChanged(int)));
    innerslider->setOrientation(Qt::Horizontal);

    innerslider->setGeometry(0,0,width(),height()/2);

    QVector<QString>::iterator iter_list;
    int i=0;
    for (iter_list=list.begin();iter_list!=list.end();iter_list++)
    {
        QString term=*iter_list;
        QLabel *lebalterm=new QLabel(this);
        labelvector.push_back(lebalterm);
        lebalterm->setText(term);
        lebalterm->setGeometry(i*width()/(list.length()-1),height()/2,50,height()/2);
        i++;
    }
    resize(width()+80,height());
}



void multistatusSlider::on_Slider_valueChanged(int value)
{
    emit StatusChange(savedvector[value]);
    qDebug()<<savedvector[value];
}
