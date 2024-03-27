#include "situationalplan.h"
#include "QMessageBox"
#include "include/FILE_manage/f_manager.h"
SituationalPlan::SituationalPlan(QWidget *parent)
    : QWidget{parent}
{
    this->move(1400,0);
    resize(200,130);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    // setAttribute(Qt::WA_TranslucentBackground);

    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    frame=new QFrame(this);
    frame->resize(500,130);
    pickpoints_check=new QPushButton(frame);
    pickpoints_check->setText("选点完成");
    pickpoints_check->setGeometry(0,0,100,30);
    pickpoints_check->hide();

    quitrecord=new QPushButton(frame);
    quitrecord->setText("终止录点");
    quitrecord->setGeometry(0,0,100,30);
    quitrecord->hide();

    loadtaskfile=new QPushButton(frame);
    loadtaskfile->setText("加载路径文件");
    loadtaskfile->setGeometry(100,0,100,30);

    pickpoints=new QPushButton(frame);
    pickpoints->setText("地图选点");
    pickpoints->setGeometry(0,30,100,30);

    autogoback=new QPushButton(frame);
    autogoback->setText("自动返航");
    autogoback->setGeometry(0,60,100,30);

    recordpoints=new QPushButton(frame);
    recordpoints->setText("航点录制");
    recordpoints->setGeometry(0,90,100,30);

    //connect(pickpoints,SIGNAL(clicked()),this,SLOT(On_Sendcommand()));
    connect(pickpoints,SIGNAL(clicked()),this,SLOT(On_finishpointsselection_command()));
    connect(pickpoints_check,SIGNAL(clicked()),this,SLOT(On_hiding_pickpoints_check_command()));
    connect(autogoback,SIGNAL(clicked()),this,SLOT(On_Send_autogoback_command()));
    connect(recordpoints,SIGNAL(clicked()),this,SLOT(On_startrecord_command()));
    connect(quitrecord,SIGNAL(clicked()),this,SLOT(On_hiding_quitrecord_check_command()));
    connect(loadtaskfile,SIGNAL(clicked()),this,SLOT(On_loadingfile_command()));

}

void SituationalPlan::On_Send_autogoback_command()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("任务规划");
    msgBox.setText("确认下发自动返航？");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {

    }
    else
    {
        //什么都不做
    }
    emit sig_autoNavi_back();
}

void SituationalPlan::On_finishpointsselection_command()
{
    pickpoints_check->show();
    //释放信号让map模块干活
    emit sig_start_record_points();
}

void SituationalPlan::On_hiding_pickpoints_check_command()
{
    pickpoints_check->hide();

    QMessageBox msgBox;
    msgBox.setWindowTitle("任务规划");
    msgBox.setText("确认下发坐标点？");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {

    }
    else
    {
        //什么都不做
    }
    emit sig_stop_record_points();
}

void SituationalPlan::On_startrecord_command()
{
    quitrecord->show();
    QMessageBox msgBox;
    msgBox.setWindowTitle("任务规划");
    msgBox.setText("确认下发自动录制指令？");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {

    }
    else
    {
        //什么都不做
    }


}

void SituationalPlan::On_hiding_quitrecord_check_command()
{
    quitrecord->hide();
    QMessageBox msgBox;
    msgBox.setWindowTitle("任务规划");
    msgBox.setText("保存任务文件？");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {

    }
    else
    {
        //什么都不做
    }
}

void SituationalPlan::On_loadingfile_command()
{
    QString filename=f_FileOpen();
}
