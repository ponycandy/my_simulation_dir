#include "statusdisplay.h"

StatusDisplay::StatusDisplay()
{
    textcolor="color:rgba(0,255,0,0.5);";
    resize(800,1000);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background-color: rgba(68, 125, 0,0)");
    int x=0,y=0,height=30,width=400,Intergel=40;
    linear_velocity=new QLabel(this);
    linear_velocity->setAlignment(Qt::AlignLeft);
    linear_velocity->setGeometry(x,y,width,height);
    y+=Intergel;
    angular_velocity=new QLabel(this);
    angular_velocity->setAlignment(Qt::AlignLeft);
    angular_velocity->setGeometry(x,y,width,height);
    y+=Intergel;
    latitude=new QLabel(this);
    latitude->setAlignment(Qt::AlignLeft);
    latitude->setGeometry(x,y,width,height);
    y+=Intergel;
    longitude=new QLabel(this);
    longitude->setAlignment(Qt::AlignLeft);
    longitude->setGeometry(x,y,width,height);
    y+=Intergel;
    altitude=new QLabel(this);
    altitude->setAlignment(Qt::AlignLeft);
    altitude->setGeometry(x,y,width,height);
    y+=Intergel;
    BatteryHealthy=new QLabel(this);
    BatteryHealthy->setAlignment(Qt::AlignLeft);
    BatteryHealthy->setGeometry(x,y,width,height);
    y+=Intergel;
    BatteryTemprature=new QLabel(this);
    BatteryTemprature->setAlignment(Qt::AlignLeft);
    BatteryTemprature->setGeometry(x,y,width,height);
    y+=Intergel;
    motorRPM_1=new QLabel(this);
    motorRPM_1->setAlignment(Qt::AlignLeft);
    motorRPM_1->setGeometry(x,y,width,height);
    y+=Intergel;
    motorRPM_2=new QLabel(this);
    motorRPM_2->setAlignment(Qt::AlignLeft);
    motorRPM_2->setGeometry(x,y,width,height);
    y+=Intergel;
    motorRPM_3=new QLabel(this);
    motorRPM_3->setAlignment(Qt::AlignLeft);
    motorRPM_3->setGeometry(x,y,width,height);
    y+=Intergel;
    motorRPM_4=new QLabel(this);
    motorRPM_4->setAlignment(Qt::AlignLeft);
    motorRPM_4->setGeometry(x,y,width,height);
    y+=Intergel;
    acc_x=new QLabel(this);
    acc_x->setAlignment(Qt::AlignLeft);
    acc_x->setGeometry(x,y,width,height);
    y+=Intergel;
    acc_y=new QLabel(this);
    acc_y->setAlignment(Qt::AlignLeft);
    acc_y->setGeometry(x,y,width,height);
    y+=Intergel;
    acc_z=new QLabel(this);
    acc_z->setAlignment(Qt::AlignLeft);
    acc_z->setGeometry(x,y,width,height);
    y+=Intergel;
    roll=new QLabel(this);
    roll->setAlignment(Qt::AlignLeft);
    roll->setGeometry(x,y,width,height);
    y+=Intergel;
    pitch=new QLabel(this);
    pitch->setAlignment(Qt::AlignLeft);
    pitch->setGeometry(x,y,width,height);
    y+=Intergel;
    yaw=new QLabel(this);
    yaw->setAlignment(Qt::AlignLeft);
    yaw->setGeometry(x,y,width,height);
    y+=height;
}

void StatusDisplay::update_linear_velocity(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    linear_velocity->setStyleSheet(textcolor);
    linear_velocity->setFont(ft);
    linear_velocity->setText("linear velocity:"+QString::number(value, 'f', 1)+"m/s");
}

void StatusDisplay::update_angular_velocity(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    angular_velocity->setStyleSheet(textcolor);
    angular_velocity->setFont(ft);
    angular_velocity->setText("angular velocity:"+QString::number(value, 'f', 1)+"rad/s");
}

void StatusDisplay::update_latitude(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    latitude->setStyleSheet(textcolor);
    latitude->setFont(ft);
    latitude->setText("lat:"+QString::number(value, 'f', 8)+" ");
}

void StatusDisplay::update_altitude(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    altitude->setStyleSheet(textcolor);
    altitude->setFont(ft);
    altitude->setText("alti: "+QString::number(value, 'f', 8)+"m");

}

void StatusDisplay::update_BatteryTemprature(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    BatteryTemprature->setStyleSheet(textcolor);
    BatteryTemprature->setFont(ft);
    BatteryTemprature->setText("temp:"+QString::number(value, 'f', 8)+" ");
}

void StatusDisplay::update_motorRPM_2(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::green);
    motorRPM_2->setStyleSheet(textcolor);
    motorRPM_2->setFont(ft);
    motorRPM_2->setStyleSheet(textcolor);

    motorRPM_2->setText("rpm motor2: "+QString::number(value, 'f', 3)+" RPM");

}

void StatusDisplay::update_motorRPM_3(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    motorRPM_3->setStyleSheet(textcolor);
    motorRPM_3->setFont(ft);
    motorRPM_3->setText("rpm motor3: "+QString::number(value, 'f', 8)+" RPM");

}

void StatusDisplay::update_acc_x(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    acc_x->setStyleSheet(textcolor);
    acc_x->setFont(ft);
    acc_x->setText("ACC x:"+QString::number(value, 'f', 3)+" m/s2");

}

void StatusDisplay::update_acc_y(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    acc_y->setStyleSheet(textcolor);
    acc_y->setFont(ft);
    acc_y->setText("ACC y:"+QString::number(value, 'f', 3)+" m/s2");

}

void StatusDisplay::update_acc_z(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    acc_z->setStyleSheet(textcolor);
    acc_z->setFont(ft);
    acc_z->setText("Acc Z: "+QString::number(value, 'f', 3)+" m/s2");

}

void StatusDisplay::update_pitch(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    pitch->setStyleSheet(textcolor);
    pitch->setFont(ft);
    pitch->setText("pitch: "+QString::number(value, 'f', 3)+" rad");

}

void StatusDisplay::update_yaw(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    yaw->setStyleSheet(textcolor);
    yaw->setFont(ft);
    yaw->setText("yaw: "+QString::number(value, 'f', 3)+" rad");

}

void StatusDisplay::update_roll(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    roll->setStyleSheet(textcolor);
    roll->setFont(ft);
    roll->setText("roll: "+QString::number(value, 'f', 3)+" rad");
}

void StatusDisplay::update_motorRPM_4(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    motorRPM_4->setStyleSheet(textcolor);
    motorRPM_4->setFont(ft);
    motorRPM_4->setText("rpm motor4:"+QString::number(value, 'f', 3)+" RPM");

}

void StatusDisplay::update_motorRPM_1(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    motorRPM_1->setStyleSheet(textcolor);
    motorRPM_1->setFont(ft);
    motorRPM_1->setText("rpm motor1:"+QString::number(value, 'f', 3)+" ");

}

void StatusDisplay::update_BatteryHealthy(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    BatteryHealthy->setStyleSheet(textcolor);
    BatteryHealthy->setFont(ft);
    BatteryHealthy->setText("SOC:"+QString::number(100*value, 'f', 3)+" %");
}

void StatusDisplay::update_longitude(double value)
{
    QPalette label_pe;
    QFont ft;
    ft.setPointSize(20);
    label_pe.setColor(QPalette::WindowText, Qt::white);
    longitude->setStyleSheet(textcolor);
    longitude->setFont(ft);
    longitude->setText("long:"+QString::number(value, 'f', 8)+" ");
}

