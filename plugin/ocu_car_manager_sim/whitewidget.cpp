#include "whitewidget.h"
#include "ui_whitewidget.h"
#include "QStyleOption"
#include "QPainter"
whitewidget::whitewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::whitewidget)
{
    ui->setupUi(this);
    button=new QPushButton(this);
    button->resize(100,100);
    frame=new QFrame(this);
    frame->resize(1280,720);
    frame->setStyleSheet("QFrame { background-image:url(:/b_img/background.jpeg)}");
    //插入背景图片
    // setAutoFillBackground(true);
    // QPalette palette = this->palette();
    // //palette.setColor(QPalette::Window, Qt::red);  // 设置背景色
    // //palette.setBrush(this->backgroundRole(), Qt::black);// 设置背景色
    // palette.setBrush(QPalette::Window,
    //                  QBrush(QPixmap(":/b_img/background.jpeg").scaled(
    //                      this->size(),
    //                      Qt::IgnoreAspectRatio,
    //                      Qt::SmoothTransformation)));
    // this->setPalette(palette);
}

whitewidget::~whitewidget()
{
    delete ui;
}

