#include "startwidget.h"
#include "ui_startwidget.h"
#include "test_bit201_communication_pluginActivator.h"
#include "QtDebug"
startwidget::startwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startwidget)
{
    ui->setupUi(this);
    m_service=
    test_bit201_communication_pluginActivator::getService<Tcpcommunicateservice>("Tcpcommunicateservice");
    m_service_1=
    test_bit201_communication_pluginActivator::getService<TCPserverservice>("TCPserverservice");
    m_service_1->startlisten(8001);
    m_service_1->Bind_Slot(this,SLOT(datarecieved(QByteArray)));
    m_service->setport("8001","127.0.0.1");
    m_service->connectport();
}

startwidget::~startwidget()
{
    delete ui;
}

void startwidget::on_pushButton_clicked()
{
    char pc[2];
    pc[0]=0x01;
    pc[1]=0x02;

    QByteArray buffer;
    buffer.setRawData(pc,2);
    m_service->send(buffer);
}
void startwidget::datarecieved(QByteArray data)
{
    qDebug()<<"hello";

}
