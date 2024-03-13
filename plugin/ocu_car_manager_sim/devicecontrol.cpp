#include "devicecontrol.h"
#include <QMessageBox>
#include <ocu_car_manager_simActivator.h>
Devicecontrol::Devicecontrol(QWidget *parent)
    : QWidget{parent}
{

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    // setAttribute(Qt::WA_TranslucentBackground);
    resize(300,400);
    frame=new QFrame(this);
    frame->resize(800,1000);

    chasis_powered_slider=new multistatusSlider(this);
    chasis_powered_slider->move(20,20);
    chasis_powered_slider->resize(200,50);
    QVector<QString> chasis_powered_sliderlist;
    chasis_powered_sliderlist.push_back("底盘下电");
    chasis_powered_sliderlist.push_back("底盘上电");
    chasis_powered_slider->init(chasis_powered_sliderlist);

    workload_powered_slider=new multistatusSlider(this);
    workload_powered_slider->move(20,80);
    workload_powered_slider->resize(200,50);
    QVector<QString> workload_powered_sliderlist;
    workload_powered_sliderlist.push_back("载荷下电");
    workload_powered_sliderlist.push_back("载荷使能");
    workload_powered_sliderlist.push_back("载荷上电");
    workload_powered_sliderlist.push_back("载荷解锁");
    workload_powered_slider->init(workload_powered_sliderlist);

    shift_change_slider=new multistatusSlider(this);
    shift_change_slider->move(20,140);
    shift_change_slider->resize(200,50);
    QVector<QString> shift_change_sliderlist;
    shift_change_sliderlist.push_back("空挡");
    shift_change_sliderlist.push_back("前进挡");
    shift_change_sliderlist.push_back("倒挡");
    shift_change_slider->init(workload_powered_sliderlist);

    weapon_change_slider=new multistatusSlider(this);
    weapon_change_slider->move(20,200);
    weapon_change_slider->resize(200,50);
    QVector<QString> weapon_change_sliderlist;
    weapon_change_sliderlist.push_back("武器下电");
    weapon_change_sliderlist.push_back("武器解锁");
    weapon_change_slider->init(weapon_change_sliderlist);

    button=new QPushButton(frame);
    button->setGeometry(20,260,50,20);
    button->setText("下发");

    connect(button,SIGNAL(clicked()),this,SLOT(On_Sendcommand()));
    ocu_car_manager_simActivator::publishsignal(this,SIGNAL(sig_update_chasis_state_mode(int,int,int)),"OCU_SIM_CHASISDEVICESTATE_UPDATE",Qt::QueuedConnection);

}

void Devicecontrol::On_Sendcommand()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("车辆设备状态修改");
    msgBox.setText("确认下发");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok)
    {

        // m_chasiscontrol.header=0xaacc;
        // m_chasiscontrol.workload_enable=false;
        // m_chasiscontrol.chasis_enable=false;
        // m_chasiscontrol.weapon_enable=false;
        // m_chasiscontrol.set_control=short(stop);
        // m_chasiscontrol.speedlimit=12;
        emit sig_update_chasis_state_mode(workload_powered_slider->innerslider->value(),
                                       chasis_powered_slider->innerslider->value(),
                                       weapon_change_slider->innerslider->value() );
   //     emit sig_update_chasis_state_mode(chasisslider->innerslider->value(),speedinput->text().toDouble());
    }
    else
    {
        //什么都不做
    }

}
