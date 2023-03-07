#include "simulatorwidget.h"
#include "ui_simulatorwidget.h"

simulatorWidget::simulatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::simulatorWidget)
{
    ui->setupUi(this);
    Vbox=new QVBoxLayout;
    this->setLayout(Vbox);
//    this->ui
//    HBox->addWidget()
}

simulatorWidget::~simulatorWidget()
{
    delete ui;
}
