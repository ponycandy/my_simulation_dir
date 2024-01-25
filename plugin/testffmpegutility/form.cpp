#include "form.h"
#include "ui_form.h"
#include "testffmpegutilityActivator.h"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
//    m_service=testffmpegutilityActivator::getService<VideoCoreservice>("VideoCoreservice");
//    ui->gridLayout->addWidget(m_service->getVideoPlayerWindow());
//    m_service->playlocalvideo("test.mp4");
//    this->setGeometry(0,0,1280,720);
//    this->showFullScreen();
}

Form::~Form()
{
    delete ui;
}
