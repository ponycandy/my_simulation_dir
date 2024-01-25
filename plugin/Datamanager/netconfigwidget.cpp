#include "netconfigwidget.h"
#include "ui_netconfigwidget.h"
#include <QtDebug>
#include <QFile>
#include <xtlevent.h>
#include "event/eventype.h"
#include "xmlcore.h"
#include <DatamanagerActivator.h>
Netconfigwidget::Netconfigwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Netconfigwidget)
{
    ui->setupUi(this);
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

    xmlCore xmlreader("./config/vehicleCONFIG/vehiclenetconfig.xml");
    int TotalNumber;
    xmlreader.xmlRead("TotalNumber",TotalNumber);
    QVector<QString> filelists;
    for(int i=1;i<=TotalNumber;i++)
    {
        QString name="VehicleName"+QString::number(i);
        std::string contained_name;
        xmlreader.xmlRead(name.toStdString(),contained_name);
        filelists.push_back(QString::fromStdString(contained_name));
    }
    int car_count=1;
    while(car_count<=TotalNumber)
    {
        QString fname="./config/vehicleCONFIG/"+filelists[car_count-1]+".xml";
        xmlCore carxmlreader(fname.toStdString());

        std::string username_S;carxmlreader.xmlRead("username_S",username_S);
        std::string password_S;carxmlreader.xmlRead("password_S",password_S);
        std::string topicname_S;carxmlreader.xmlRead("topicname_S",topicname_S);
        std::string port_S;carxmlreader.xmlRead("port_S",port_S);
        std::string host_S;carxmlreader.xmlRead("host_S",host_S);
        std::string cilentID_S;carxmlreader.xmlRead("cilentID_S",cilentID_S);
        std::string username_R;carxmlreader.xmlRead("username_R",username_R);
        std::string password_R;carxmlreader.xmlRead("password_R",password_R);
        std::string topicname_R;carxmlreader.xmlRead("topicname_R",topicname_R);
        std::string port_R;carxmlreader.xmlRead("port_R",port_R);
        std::string host_R;carxmlreader.xmlRead("host_R",host_R);
        std::string cilentID_R;carxmlreader.xmlRead("cilentID_R",cilentID_R);
        std::string videoAddress;carxmlreader.xmlRead("videoAddress",cilentID_R);
        videoAddresses.push_back(QString::fromStdString(videoAddress));

        QString vehiclename=filelists[car_count-1];
        carnames.push_back(vehiclename);

        availabe_row=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(availabe_row);
        ui->tableWidget->setItem(availabe_row,0,new QTableWidgetItem(QString::number(car_count)));
        ui->tableWidget->setItem(availabe_row,1,new QTableWidgetItem(QString::fromStdString(cilentID_S)));
        ui->tableWidget->setItem(availabe_row,2,new QTableWidgetItem(QString::fromStdString(host_S)));
        ui->tableWidget->setItem(availabe_row,3,new QTableWidgetItem(QString::fromStdString(port_S)));
        ui->tableWidget->setItem(availabe_row,4,new QTableWidgetItem(QString::fromStdString(topicname_S)));
        ui->tableWidget->setItem(availabe_row,5,new QTableWidgetItem(QString::fromStdString(username_S)));
        ui->tableWidget->setItem(availabe_row,6,new QTableWidgetItem(QString::fromStdString(password_S)));
        ui->tableWidget->setItem(availabe_row,7,new QTableWidgetItem(QString::fromStdString(cilentID_R)));
        ui->tableWidget->setItem(availabe_row,8,new QTableWidgetItem(QString::fromStdString(host_R)));
        ui->tableWidget->setItem(availabe_row,9,new QTableWidgetItem(QString::fromStdString(port_R)));
        ui->tableWidget->setItem(availabe_row,10,new QTableWidgetItem(QString::fromStdString(topicname_R)));
        ui->tableWidget->setItem(availabe_row,11,new QTableWidgetItem(QString::fromStdString(username_R)));
        ui->tableWidget->setItem(availabe_row,12,new QTableWidgetItem(QString::fromStdString(password_R)));

        m_map.insert(QString::number(TotalNumber),availabe_row);
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
        m_event.m_dict.insert("vehicle_num",ui->tableWidget->item(i,0)->text());
        m_event.m_dict.insert("cilentID(S)",ui->tableWidget->item(i,1)->text());
        m_event.m_dict.insert("host(S)",ui->tableWidget->item(i,2)->text());
        m_event.m_dict.insert("port(S)",ui->tableWidget->item(i,3)->text());
        m_event.m_dict.insert("topicname(S)",ui->tableWidget->item(i,4)->text());
        m_event.m_dict.insert("username(S)",ui->tableWidget->item(i,5)->text());    m_event.m_dict.insert("vehicle_num",ui->tableWidget->item(i,0)->text());
        m_event.m_dict.insert("password(S)",ui->tableWidget->item(i,6)->text());
        m_event.m_dict.insert("cilentID(R)",ui->tableWidget->item(i,7)->text());    m_event.m_dict.insert("vehicle_num",ui->tableWidget->item(i,0)->text());
        m_event.m_dict.insert("host(R)",ui->tableWidget->item(i,8)->text());
        m_event.m_dict.insert("port(R)",ui->tableWidget->item(i,9)->text());    m_event.m_dict.insert("vehicle_num",ui->tableWidget->item(i,0)->text());
        m_event.m_dict.insert("topicname(R)",ui->tableWidget->item(i,10)->text());
        m_event.m_dict.insert("username(R)",ui->tableWidget->item(i,11)->text());
        m_event.m_dict.insert("password(R)",ui->tableWidget->item(i,12)->text());
        m_event.m_dict.insert("vehiclename",carnames[i]);
        m_event.m_dict.insert("videoAddress",videoAddresses[i]);

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
