#include "platformscontrol.h"
#include "ui_platformscontrol.h"

platformsControl::platformsControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::platformsControl)
{
    ui->setupUi(this);
}

platformsControl::~platformsControl()
{
    delete ui;
}
