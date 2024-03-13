#include "statusdisplay.h"

StatusDisplay::StatusDisplay()
{
    resize(800,600);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background-color: rgba(68, 125, 0,0)");
    int x=0,y=0,height=20,width=200;
    linear_velocity=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    angular_velocity=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    latitude=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    longitude=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    altitude=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    BatteryHealthy=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    BatteryTemprature=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    motorRPM_1=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    motorRPM_2=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    motorRPM_3=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    motorRPM_4=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    acc_x=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    acc_y=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    acc_z=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    roll=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    pitch=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
    yaw=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=height;
}

void StatusDisplay::update_linear_velocity(double value)
{
    linear_velocity->setText("线速度："+QString::number(value, 'f', 1)+"m/s");
}

void StatusDisplay::update_angular_velocity(double value)
{
    angular_velocity->setText("角速度："+QString::number(value, 'f', 1)+"rad/s");
}

void StatusDisplay::update_latitude(double value)
{
    latitude->setText("经度："+QString::number(value, 'f', 8));
}

void StatusDisplay::update_altitude(double value)
{
    altitude->setText("海拔："+QString::number(value, 'f', 8)+"m");

}

void StatusDisplay::update_BatteryTemprature(double value)
{
    latitude->setText("电池温度："+QString::number(value, 'f', 8)+" C");
}

void StatusDisplay::update_motorRPM_2(double value)
{
    motorRPM_2->setText("电机2转速： "+QString::number(value, 'f', 8)+" RPM");

}

void StatusDisplay::update_motorRPM_3(double value)
{
    motorRPM_3->setText("电机3转速： "+QString::number(value, 'f', 8)+" RPM");

}

void StatusDisplay::update_acc_x(double value)
{
    acc_x->setText("x轴加速度： "+QString::number(value, 'f', 3)+" m/s2");

}

void StatusDisplay::update_acc_y(double value)
{
    acc_y->setText("y轴加速度： "+QString::number(value, 'f', 3)+" m/s2");

}

void StatusDisplay::update_acc_z(double value)
{
    acc_z->setText("z轴加速度: "+QString::number(value, 'f', 3)+" m/s2");

}

void StatusDisplay::update_pitch(double value)
{
    pitch->setText("俯仰角: "+QString::number(value, 'f', 3)+" rad");

}

void StatusDisplay::update_yaw(double value)
{
    yaw->setText("偏航角: "+QString::number(value, 'f', 3)+" rad");

}

void StatusDisplay::update_roll(double value)
{
    roll->setText("滚转角: "+QString::number(value, 'f', 3)+" rad");
}

void StatusDisplay::update_motorRPM_4(double value)
{
    motorRPM_4->setText("电机4转速： "+QString::number(value, 'f', 3)+" RPM");

}

void StatusDisplay::update_motorRPM_1(double value)
{
    motorRPM_1->setText("电机1转速： "+QString::number(value, 'f', 3)+" RPM");

}

void StatusDisplay::update_BatteryHealthy(double value)
{
    BatteryHealthy->setText("剩余电量： "+QString::number(100*value, 'f', 3)+" %");
}

void StatusDisplay::update_longitude(double value)
{
    longitude->setText("纬度："+QString::number(value, 'f', 8));
}

