#include "form.h"
#include "ui_form.h"
#include "testffmpegutilityActivator.h"
#include "qpalette"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{

    ui->setupUi(this);
    m_service=testffmpegutilityActivator::getService<VideoCoreservice>("VideoCoreservice");
    ui->gridLayout->addWidget(m_service->getVideoPlayerWindow());
    m_service->playlocalvideo("test.mp4");
    this->setGeometry(0,0,1280,720);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);//去掉标题栏
    setAttribute(Qt::WA_TranslucentBackground, true);//设置窗口背景透明

    this->show();
}

Form::~Form()
{
    delete ui;
}
