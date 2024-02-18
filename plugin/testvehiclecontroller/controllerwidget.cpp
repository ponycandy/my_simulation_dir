#include "controllerwidget.h"
#include "ui_controllerwidget.h"

controllerwidget::controllerwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::controllerwidget)
{
    ui->setupUi(this);
}

controllerwidget::~controllerwidget()
{
    delete ui;
}

void controllerwidget::on_pushButton_clicked()
{
    emit send_one();
}

