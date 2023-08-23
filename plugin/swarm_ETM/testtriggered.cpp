#include "testtriggered.h"
#include "ui_testtriggered.h"

TestTriggered::TestTriggered(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestTriggered)
{
    ui->setupUi(this);
}

TestTriggered::~TestTriggered()
{
    delete ui;
}

void TestTriggered::on_pushButton_clicked()
{
    emit  trigeronce();
}

