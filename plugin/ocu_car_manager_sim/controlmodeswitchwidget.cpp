#include "controlmodeswitchwidget.h"
#include <QMessageBox>
#include <ocu_car_manager_simActivator.h>
ControlModeSwitchWidget::ControlModeSwitchWidget(QWidget *parent)
    : QWidget{parent}
{

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    // setAttribute(Qt::WA_TranslucentBackground);
    resize(300,250);
    frame=new QFrame(this);
    frame->resize(500,500);
    speedinput=new QLineEdit(frame);
    chasisslider=new multistatusSlider(this);
    chasisslider->move(20,20);
    chasisslider->resize(200,50);
    QVector<QString> valuelist;
    valuelist.push_back("机构停止");
    controlmode="机构停止";
    valuelist.push_back("手动操控");
    valuelist.push_back("自动驾驶");
    SpeedLimit=new QLabel(frame);
    butt=new QPushButton(frame);
    SpeedLimit->setText("最大限速km/h:");
    butt->setGeometry(20,140,100,30);
    butt->setText("指令下发");
    SpeedLimit->setGeometry(20,100,100,30);
    speedinput->setGeometry(100,100,50,30);
    speedinput->setText("12");
    chasisslider->init(valuelist);

    connect(butt,SIGNAL(clicked()),this,SLOT(On_Sendcommand()));
    connect(chasisslider,SIGNAL(StatusChange(QString)),this,SLOT(On_updatecontrolmode(QString)));
    ocu_car_manager_simActivator::publishsignal(this,SIGNAL(sig_updateControlmode(short,double)),"OCU_SIM_CONTROLMODE_UPDATE",Qt::QueuedConnection);

}

void ControlModeSwitchWidget::On_Sendcommand()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("驾驶指令下发");
    msgBox.setText("模式切换");
    msgBox.setInformativeText("切换为"+controlmode);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {
        emit sig_updateControlmode(chasisslider->innerslider->value(),speedinput->text().toDouble());
    }
    else
    {
//什么都不做
    }

}

void ControlModeSwitchWidget::On_updatecontrolmode(QString name)
{
    controlmode=name;
}
