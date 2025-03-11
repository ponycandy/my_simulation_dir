#include "netconfigwidget.h"
#include "ui_netconfigwidget.h"
#include <QtDebug>
#include <QFile>
#include <xtlevent.h>
#include "event/eventype.h"
#include "xmlcore.h"
#include <DatamanagerActivator.h>
#include <QDirIterator>

Netconfigwidget::Netconfigwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Netconfigwidget)
{
    ui->setupUi(this);
    setStyleSheet("background-color: white");
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(13);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList header;
    header<<""<<"cilentID(S)"<<"host(S)"<<"port(S)"<<"topicname(S)"<<"username(S)"<<"password(S)"
         <<"cilentID(R)"<<"host(R)"<<"port(R)"<<"topicname(R)"<<"username(R)"<<"password(R)";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    readconfig();
}

Netconfigwidget::~Netconfigwidget()
{
    delete ui;
}

void Netconfigwidget::readconfig()
{
    QString configdirectory="./config/vehicleconfig";
    QDir dir(configdirectory);
    QDirIterator it(configdirectory, QDir::Files, QDirIterator::Subdirectories);
    int car_count=1;
    while (it.hasNext()) {
        it.next();
         QFile file(dir.filePath(it.fileName()));
         QFileInfo fileInfo(file);
        qDebug() << fileInfo.absoluteFilePath();

        xmlCore carxmlreader(fileInfo.absoluteFilePath().toStdString());

        std::string port_S;carxmlreader.xmlRead("port",port_S);
        std::string host_S;carxmlreader.xmlRead("host",host_S);
        std::string cilentID_S;carxmlreader.xmlRead("cilentID",cilentID_S);

        QString vehiclename=it.fileName().chopped(4);
        carnames.push_back(vehiclename);

        availabe_row=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(availabe_row);
        ui->tableWidget->setItem(availabe_row,0,new QTableWidgetItem(QString::number(car_count)));
        ui->tableWidget->setItem(availabe_row,1,new QTableWidgetItem(vehiclename));
        ui->tableWidget->setItem(availabe_row,2,new QTableWidgetItem(QString::fromStdString(cilentID_S)));
        ui->tableWidget->setItem(availabe_row,3,new QTableWidgetItem(QString::fromStdString(host_S)));
        ui->tableWidget->setItem(availabe_row,4,new QTableWidgetItem(QString::fromStdString(port_S)));

        car_count++;

    }


}

void Netconfigwidget::on_pushButton_clicked()
{
}

void Netconfigwidget::on_pushButton_3_clicked()
{
}

void Netconfigwidget::on_pushButton_2_clicked()
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        XTLevent m_event;
        m_event.eventname=UCSEVENT::MQTTNETSET;
        m_event.m_dict.insert("cilentID(S)",ui->tableWidget->item(i,1)->text());
        m_event.m_dict.insert("host(S)",ui->tableWidget->item(i,2)->text());
        m_event.m_dict.insert("port(S)",ui->tableWidget->item(i,3)->text());
        m_event.m_dict.insert("vehiclename",carnames[i]);

        DatamanagerActivator::postevent(m_event);

    }
}

void Netconfigwidget::on_pushButton_4_clicked()
{

}

void Netconfigwidget::on_horizontalSlider_valueChanged(int value)
{
    ui->label_17->setText(value ? "On" : "off");
    if(value==1)
    {
        XTLevent event;
        event.eventname=UCSEVENT::MQTTSTART;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            event.m_dict.insert("vehicle_num",ui->tableWidget->item(i,0)->text());
            DatamanagerActivator::postevent(event);

        }
    }
    else
    {
        XTLevent event;
        event.eventname=UCSEVENT::MQTTSTOP;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            event.m_dict.insert("vehicle_num",ui->tableWidget->item(i,0)->text());
            DatamanagerActivator::postevent(event);

        }
    }
}

void Netconfigwidget::on_horizontalSlider_2_valueChanged(int value)
{
    ui->label_19->setText(value ? "On" : "off");

    XTLevent event;
    event.eventname=UCSEVENT::STARTROSLOOP;
    event.m_dict.insert("property",value);
    DatamanagerActivator::postevent(event);
}
