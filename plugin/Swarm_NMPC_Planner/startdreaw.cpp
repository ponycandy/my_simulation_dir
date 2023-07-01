#include "startdreaw.h"
#include "ui_startdreaw.h"

startdreaw::startdreaw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startdreaw)
{
    ui->setupUi(this);
}

startdreaw::~startdreaw()
{
    delete ui;
}

void startdreaw::on_pushButton_clicked()
{
    emit sig_start(m_polys,fx,fy);
}

