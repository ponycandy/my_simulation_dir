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

