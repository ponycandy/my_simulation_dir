#include "form.h"
#include "ui_form.h"
#include "testffmpegutilityActivator.h"
#include "qpalette"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{

    ui->setupUi(this);
    widg=new InteractiveMap;
    this->show();
}

Form::~Form()
{
    delete ui;
}
