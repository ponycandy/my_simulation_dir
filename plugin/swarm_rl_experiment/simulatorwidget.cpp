#include "simulatorwidget.h"
#include "ui_simulatorwidget.h"

simulatorWidget::simulatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::simulatorWidget)
{
    ui->setupUi(this);
    Vbox=new QVBoxLayout;
    this->setLayout(Vbox);
}

simulatorWidget::~simulatorWidget()
{
    delete ui;
}
