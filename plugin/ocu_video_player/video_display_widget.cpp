#include "video_display_widget.h"
#include "ui_video_display_widget.h"
#include <QTimer>
#include <QDebug>
#include <cstdlib>
video_display_widget::video_display_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video_display_widget)
{
    ui->setupUi(this);
    mode=0;//0 is play stream,1 is play local
    ui->widget->setStyleSheet("background-color: white");
    ui->widget_2->setStyleSheet("background-color: white");

}

video_display_widget::~video_display_widget()
{
    delete ui;
}




void video_display_widget::slotOnStart()
{
    if(mode==0)//remote
    {
        QString cmd="start cmd.exe /k ffplay -fflags nobuffer -flags low_delay -framedrop rtmp://"+pathname+" -noborder -left 300 -top 420 -vf scale=720:480";
        std::system(cmd.toLatin1().data());
    }
    else//local
    {
        QString cmd="start cmd.exe /k ffplay "+ QString(" -noborder -left 300 -top 420 -x 720 -y 480 ")+pathname;
        std::system(cmd.toLatin1().data());
    }
    //更改透明度！
    // Set the widget as transparent
    ui->widget_video->setWindowOpacity(0);
    ui->widget_video->setWindowOpacity(0);
    ui->widget_video->setAttribute(Qt::WA_TranslucentBackground);
    ui->widget_video->setAttribute(Qt::WA_NoSystemBackground);
    ui->widget_video->setWindowFlags(Qt::FramelessWindowHint);
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

