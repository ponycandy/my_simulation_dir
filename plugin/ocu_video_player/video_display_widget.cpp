#include "video_display_widget.h"
#include "ui_video_display_widget.h"
#include <QTimer>
#include <QDebug>
#include <cstdlib>
video_display_widget::video_display_widget(QWidget *parent) :
    QWidget(parent)
{
    mode=0;//0 is play stream,1 is play local
    slider=new QSlider(this);
    //slider->setStyleSheet("QSlider::groove:horizontal { background: green; }");

    slider->setStyleSheet("QSlider::groove:horizontal { background: #00FF00; }");
    slider->setStyleSheet("QSlider::handle:horizontal { background: #00FF00; }");

    customvslider=new HronSlider(this);
    customhslider=new CustomSlider(this);
    customhslider->move(500,864);
    customvslider->move(200,300);
    battery=new BatteryStatus(this);
    battery->move(1000,100);
    direct=new DirectionHron(this);
    direct->move(600,100);
    resize(1680,1080);
    slider->setMaximum(1);
    connect(slider,SIGNAL(sliderMoved(int)),this,SLOT(on_horizontalSlider_valueChanged(int)));
    slider->setGeometry(5,5,40,10);
    slider->setOrientation(Qt::Horizontal);
    //画十字叉
    int length=50;
    int width=3;
    cross=new crossaxle(this);
    cross->move(700,500);
    vid_x=120;
    vid_y=0;
    vid_width=1470;
    vid_height=1080;
    //将状态信息叠加在上面
    //仿照UAV的UI界面，下面水平标尺作为方向角显示，上方作为指南针显示
//左侧和右侧分别对应角速度和线速度
//横滚角没有必要，但是可以凑一下

    //显示运动轨迹的功能暂时也没有必要（见华为HUD）
}

video_display_widget::~video_display_widget()
{
    delete this;
}




void video_display_widget::slotOnStart()
{
    if(mode==0)//remote
    {
        QString cmd="start cmd.exe /k ffplay -fflags nobuffer -flags low_delay -framedrop rtmp://"
                      +pathname+" -noborder -left "+QString::number(vid_x)
                      +" -top "+QString::number(vid_y)+
                      " -vf scale="+QString::number(vid_width)+":"+QString::number(vid_height);
        std::system(cmd.toLatin1().data());
    }
    else//local
    {
        QString cmd="start cmd.exe /k ffplay "+ QString(" -noborder -left ")+QString::number(vid_x)
                      +" -top "+QString::number(vid_y)+" -x " +QString::number(vid_width)+
                      " -y "+QString::number(vid_height)+"  "+pathname;
        std::system(cmd.toLatin1().data());
    }
    //更改透明度！
    // Set the widget as transparent
    this->setWindowOpacity(0);
    this->setWindowOpacity(0);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_NoSystemBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void video_display_widget::slotOnStop()
{
    QString cmd=" taskkill /f /im ffplay.exe";
    std::system(cmd.toLatin1().data());

//    cmd=" taskkill /f /im cmd.exe";
//    std::system(cmd.toLatin1().data());
}

void video_display_widget::on_horizontalSlider_valueChanged(int value)
{
    if(value==1)
    {
        slotOnStart();
    }
    else
    {
        slotOnStop();
    }
}

