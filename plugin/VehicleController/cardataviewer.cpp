#include "cardataviewer.h"
#include "VehicleControllerActivator.h"
#include "service/Coreservice.h"
CardataViewer::CardataViewer(QWidget *parent) :
    QWidget(parent)
{

    gridLayout=new QGridLayout;
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    m_video=new videoplayer;
    //尺寸w:1680 height:1080
    m_video->resize(1680,1080);

    comboxframe=new QFrame;
    comboxframe->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    comboxframe->setAttribute(Qt::WA_TranslucentBackground);
    comboxframe->resize(130,70);
    comboBox=new QComboBox(comboxframe);
    comboBox_2=new QComboBox(comboxframe);
    widgetinfos info;
    info.x=120;
    info.y=10;
    info.wid=comboxframe;
    all_overlays.push_back(info);

    comboBox->setGeometry(0,0,120,30);
    connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBox_currentIndexChanged(int)));
    comboBox_2->setGeometry(0,30,120,30);
    connect(comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBox_currentIndexChanged(int)));

    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->addWidget(m_video);

    this->setLayout(gridLayout);
    nullwidget=new QWidget;
}

CardataViewer::~CardataViewer()
{
    delete this;
}


void CardataViewer::clearcombox()
{
    comboBox->clear();
}

void CardataViewer::display_combox()
{
    if(combox_state==true)
    {
        // comboBox->hide();
        // comboBox_2->hide();
        comboxframe->hide();

        combox_state=false;
    }
    else
    {
        comboxframe->move(120,10);
        comboxframe->show();
        // comboBox->show();
      //  comboxframe->raise();
        // comboBox_2->show();
        // comboBox_2->raise();
        combox_state=true;
    }
}

void CardataViewer::Addwidget(QWidget *windows, QString vehicle, QString windowname)
{
    if(temp_1.contains(vehicle))
    {

    }
    else
    {
        comboBox->addItem(vehicle);
       // comboBox->hide();
        temp_1.insert(vehicle,0);
    }
    if(temp_2.contains(windowname))
    {

    }
    else
    {
        temp_2.insert(windowname,0);
        comboBox_2->addItem(windowname);
    }
    m_video->addWidget(windows);

    two_2_1map.insert(vehicle+windowname,windows);
    //然后加combox
//M_video中的界面会覆盖复选框

}

void CardataViewer::changeTowidget(QString vehicle, QString windowname)
{
    //首先设置Combox的名称
   // int index=comboBox->currentIndex();
    QWidget* pair=two_2_1map.value(vehicle+windowname);
    //叠加在当前界面上的所有QFrame;

    QVector<widgetinfos>::iterator iter;
    for (iter=all_overlays.begin();iter!=all_overlays.end();iter++)
    {
        widgetinfos oneinfo=*iter;

        oneinfo.wid->setParent(pair);
        oneinfo.wid->setWindowFlags(Qt::WindowFlags());
        oneinfo.wid->setGeometry(x()+oneinfo.x,y()+oneinfo.y,
                                 oneinfo.wid->width(),oneinfo.wid->height());
    }

    m_video->setCurrentWidget(pair);
}

void CardataViewer::switchview()
{
    QString vehiclename=comboBox->currentText();
    QString windowsname=comboBox_2->currentText();
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



void CardataViewer::on_comboBox_currentIndexChanged(int index)
{
    switchview();
}


void CardataViewer::on_comboBox_2_currentIndexChanged(int index)
{
    switchview();
}

