#include "cameracontroller.h"
#include "ui_cameracontroller.h"
#include <xmlcore.h>
Cameracontroller::Cameracontroller(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Cameracontroller)
{
    ui->setupUi(this);
    framerate=30;
    ui->lineEdit_2->setText(QString::number(framerate));
    timer=new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(CameraCapture()));
    xmlCore xmlfile("./config/cameraparams.xml");

    xmlfile.xmlRead("camera_num",cameranum);
    xmlfile.xmlRead("resolution_width",width);
    xmlfile.xmlRead("resolution_height",height);

    for(int i=0;i<cameranum;i++)
    {
        QString camera_name="Camera_"+QString::number(i);
        int cameraID;
        xmlfile.xmlRead(camera_name.toStdString(),cameraID);
        cameraIDlists.push_back(cameraID);
    }

}

Cameracontroller::~Cameracontroller()
{
    delete ui;
}

void Cameracontroller::on_pushButton_clicked()
{
    directory_name=f_Open_directory();
    ui->lineEdit->setText(directory_name);
}

void Cameracontroller::CameraCapture()
{
    timer->stop();
    for(int i=0;i<cameraIDlists.length();i++)
    {
        QString cmd="start cmd.exe /k  captureimage.exe "+QString::number(cameraIDlists[i])+" "+directory_name
                      +" "+ui->lineEdit_2->text()+" "+QString::number(width)+" "+QString::number(height);
        std::system(cmd.toLatin1().data());
    }
    //做完后执行文件命名对比脚本，将时间差值在一定以下的配对保存下来
}


void Cameracontroller::on_pushButton_2_clicked()
{
    QString cmd="start cmd.exe /k counter.mp3";
    std::system(cmd.toLatin1().data());
    timer->start(13500);
}




void Cameracontroller::on_pushButton_3_clicked()
{
    QString cmd=" taskkill /f /im captureimage.exe";
    std::system(cmd.toLatin1().data());
}

