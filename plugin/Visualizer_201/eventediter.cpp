#include "eventediter.h"

EventEditer::EventEditer(QWidget *parent)
    : QWidget{parent}
{
    resize(500,500);
    addevent=new QPushButton(this);
    saveevent=new QPushButton(this);
    deleteevent=new QPushButton(this);
    input_label=new QPushButton(this);

    tableWidget=new QTableWidget(this);
    select_signal=new QComboBox(this);
    select_slot=new QComboBox(this);
    extraparameter_input=new QLineEdit(this);
    select_signal->setGeometry(100,0,100,30);
    select_slot->setGeometry(100,30,100,30);
    input_label->setGeometry(100,60,100,30);
    input_label->setText("额外参数输入");
    extraparameter_input->setGeometry(200,60,200,30);//parse_command

    tableWidget->setGeometry(0,90,500,300);
    addevent->setGeometry(0,0,100,30);
    addevent->setText("添加事件");
    connect(addevent,SIGNAL(clicked()),this,SLOT(OnAddItem()));
    saveevent->setGeometry(0,30,100,30);
    saveevent->setText("保存事件");
    deleteevent->setGeometry(0,60,100,30);
    deleteevent->setText("删除事件");


    tableWidget->setObjectName(QString::fromUtf8("tableWidget"));


    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(3);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header<< "触发信号"<<"反馈信号"<<"额外参数";
    tableWidget->setHorizontalHeaderLabels(header);


    init_signal_and_slot();

    setWindowFlags(Qt::Dialog);
}

void EventEditer::init_signal_and_slot()
{
    select_signal->addItem("探测信号");
    select_signal->addItem("轨迹规划信号");
    select_signal->addItem("控制信号");

    select_slot->addItem("探测结果");
    select_slot->addItem("规划结果");
    select_slot->addItem("控制反馈");

}

void EventEditer::OnAddItem()
{
    int availabe_row= tableWidget->rowCount();
    tableWidget->insertRow(availabe_row);
    tableWidget->setItem(availabe_row,0,new QTableWidgetItem(select_signal->currentText()));
    tableWidget->setItem(availabe_row,1,new QTableWidgetItem(select_slot->currentText()));
    tableWidget->setItem(availabe_row,2,new QTableWidgetItem(extraparameter_input->text()));
}
