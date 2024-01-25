#include "cardataviewer.h"
#include "ui_cardataviewer.h"
#include "VehicleControllerActivator.h"
#include "service/Coreservice.h"
CardataViewer::CardataViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardataViewer)
{
    ui->setupUi(this);
    m_video=new videoplayer;
    ui->gridLayout->addWidget(m_video);
    nullwidget=new QWidget;
}

CardataViewer::~CardataViewer()
{
    delete ui;
}


void CardataViewer::clearcombox()
{
    ui->comboBox->clear();
}

void CardataViewer::Addwidget(QWidget *windows, QString vehicle, QString windowname)
{
    if(two_2_1map.contains(vehicle))
    {

    }
    else
    {
        ui->comboBox->addItem(vehicle);
    }
    if(combox_map_view_genre.contains(windowname))
    {

    }
    else
    {
        ui->comboBox_2->addItem(windowname);
    }
    m_video->addWidget(windows);
    QMap<QString ,QWidget*> pair;
    pair.insert(windowname,windows);
    two_2_1map.insert(vehicle,pair);
    //然后加combox


}

void CardataViewer::changeTowidget(QString vehicle, QString windowname)
{
    QMap<QString ,QWidget*> pair=two_2_1map.value(vehicle);
    m_video->setCurrentWidget(pair.value(windowname));
}

void CardataViewer::switchview()
{
    QString vehiclename=ui->comboBox->currentText();
    QString windowsname=ui->comboBox_2->currentText();
    if(vehiclename=="" ||windowsname=="" )
    {
        //切换为空界面
        m_video->setCurrentWidget(nullwidget);
    }
    else
    {
        changeTowidget(vehiclename,windowsname);
    }
}

void CardataViewer::on_pushButton_clicked()
{
    Coreservice *m_service=VehicleControllerActivator::getService<Coreservice>("Coreservice");
    m_service->changeView(UcsDefines::UCS_VIEW_KIND_MAIN);
}


void CardataViewer::on_comboBox_currentIndexChanged(int index)
{
    switchview();
}


void CardataViewer::on_comboBox_2_currentIndexChanged(int index)
{
    switchview();
}

