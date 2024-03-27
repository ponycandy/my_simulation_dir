#include "controlwidget.h"
#include "ui_controlwidget.h"

controlwidget::controlwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::controlwidget)
{
    ui->setupUi(this);
    cmd.linear=0;
    cmd.omega=0;
}

controlwidget::~controlwidget()
{
    delete ui;
}

void controlwidget::on_pushButton_clicked()
{
    cmd.linear=0.03;
    cmd.omega=0;

    somepuber->publish<jetson::motioncommand>(cmd);
}


void controlwidget::on_pushButton_2_clicked()
{
    cmd.linear=-0.03;
    cmd.omega=0;

    somepuber->publish<jetson::motioncommand>(cmd);
}


void controlwidget::on_pushButton_3_clicked()
{
    cmd.linear=0;
    cmd.omega=0;
    somepuber->publish<jetson::motioncommand>(cmd);
}


void controlwidget::on_pushButton_4_clicked()
{
    cmd.linear=0;
    cmd.omega=-0.03;
    somepuber->publish<jetson::motioncommand>(cmd);

}


void controlwidget::on_pushButton_5_clicked()
{
    cmd.linear=0;
    cmd.omega=0.03;
    somepuber->publish<jetson::motioncommand>(cmd);

}

