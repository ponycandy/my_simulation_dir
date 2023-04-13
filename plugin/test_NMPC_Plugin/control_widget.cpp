#include "control_widget.h"
#include "ui_control_widget.h"

Control_Widget::Control_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Control_Widget)
{
    ui->setupUi(this);
}

Control_Widget::~Control_Widget()
{
    delete ui;
}

void Control_Widget::on_pushButton_clicked()
{
    emit start_solving();
}
