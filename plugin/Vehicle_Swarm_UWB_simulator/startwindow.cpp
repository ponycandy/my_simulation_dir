#include "startwindow.h"
#include "ui_startwindow.h"

startwindow::startwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startwindow)
{
    ui->setupUi(this);
}

startwindow::~startwindow()
{
    delete ui;
}

void startwindow::on_pushButton_clicked()
{
    emit sigstart();
}


void startwindow::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text()=="选点")
    {
        ui->pushButton_2->setText("停止选点");
        emit sig_choose_bool(true);
    }
    else
    {
        ui->pushButton_2->setText("选点");
        emit sig_choose_bool(false);

    }
}


void startwindow::on_pushButton_3_clicked()
{
    emit sigstop();
}


void startwindow::on_pushButton_4_clicked()
{
    emit sigspin();
}

