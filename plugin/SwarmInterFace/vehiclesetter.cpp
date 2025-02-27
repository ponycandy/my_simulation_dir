#include "vehiclesetter.h"
#include "ui_vehiclesetter.h"

vehiclesetter::vehiclesetter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vehiclesetter)
{
    ui->setupUi(this);
}

vehiclesetter::~vehiclesetter()
{
    delete ui;
}
