#include "startwindow.h"
#include "ui_startwindow.h"
#include "ocu_car_manager_simActivator.h"
#include "event/OcuEventContants.h"
#include "qcoreapplication.h"
#include "service/Mapservice.h"
#include "service/VideoCoreservice.h"

startwindow::startwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startwindow),m_whitewidget(NULL),simulationconfig(NULL)
{
    ui->setupUi(this);
    setupwidget();
    m_viewManager=new ViewManager;
    simulationconfig=new simulationconfiguration;
    ocu_car_manager_simActivator::registerservice(this,"ocu_car_coreservice");
    m_service=ocu_car_manager_simActivator::getService<Coreservice>("Coreservice");
    m_service->addView(UcsDefines::UCS_VIEW_KIND_MAIN,this);
    m_service->changeView(UcsDefines::UCS_VIEW_KIND_MAIN);
    this->addView(UcsDefines::SIM_SIMULATIONCONFIG,simulationconfig);

    ocu_car_manager_simActivator::subscribevent(UcsEventConstants::TOPCI_MENU_CLICKED,this);
    //UcsEventConstants::TOPCI_MENU_CLICKED


    Mapsrvl=ocu_car_manager_simActivator::getService<MapService>("MapService");
    mapwidget=Mapsrvl->getMapwidget();
    mapwidget->move(0,0);
    mapwidget->resize(1920,1080);
    mapwidget->show();//单独显示在2号屏幕上



//前视摄像头放在HUD里面，其它摄像头放三号和四号屏幕上
    VideoCoreservice *vidservice_temp=ocu_car_manager_simActivator::getService<VideoCoreservice>("VideoCoreservice");
    VideoCoreservice* vidservice=vidservice_temp->cloneservice();

    vidservice->setrtmpPath("192.168.1.18/live/test");

    QWidget *vid_wid_1=vidservice->getVideoPlayerWindow();
    this->addView(UcsDefines::UCS_VIEW_KIND_MAIN,vid_wid_1);
    // //状态显示绑定到videoviewer上
    // initilizevideostatus(vidservice->getVideoPlayerWindow(),vehicle->vehiclename);
    situa=new SituationalPlan;
    situa->hide();
}

startwindow::~startwindow()
{
    delete ui;
}

void startwindow::setupwidget()
{
    /*初始化12个按钮，左右两边各6个，并将指针插入到节点管理器中*/
    /*左边的六个按钮*/
    m_leftWidget = new QWidget;
    m_leftWidget->setFixedSize(120,1080);
    m_leftWidget->setStyleSheet("background-color: white");

    m_leftLayout = new QVBoxLayout;
    m_leftLayout->setContentsMargins(0, 0, 0, 0);
    m_leftLayout->setSpacing(0);
    m_leftWidget->setLayout(m_leftLayout);

    for (int i = 1; i <= 6; ++i)
    {
        QToolButton *button = new QToolButton;
        button->setProperty("style", "MenuLeftButton");
        button->setFixedSize(120,181);
        button->setStyleSheet("border: 1px solid #000000;");

        QSizePolicy policy = button->sizePolicy();
        policy.setVerticalPolicy(QSizePolicy::Fixed);
        button->setSizePolicy(policy);
        m_leftLayout->addWidget(button);
        m_buttons.insert(i, button);

        connect(button, &QToolButton::clicked, this, &startwindow::onMenuClicked);
    }

    /*右边的六个按钮*/
    m_rightWidget = new QWidget;
    m_rightWidget->setFixedSize(120, 1080);
    m_rightWidget->setStyleSheet("background-color: white");

    m_rightLayout = new QVBoxLayout;
    m_rightLayout->setContentsMargins(0, 0, 0, 0);
    m_rightLayout->setSpacing(0);
    m_rightWidget->setLayout(m_rightLayout);

    for (int i = 7; i <= 12; ++i)
    {
        QToolButton *button = new QToolButton;
        button->setProperty("style", "MenuRightButton");

        button->setFixedSize(120,181);
        button->setStyleSheet("border: 1px solid #000000;");

        QSizePolicy policy = button->sizePolicy();
        policy.setVerticalPolicy(QSizePolicy::Fixed);
        button->setSizePolicy(policy);
        m_rightLayout->addWidget(button);
        m_buttons.insert(i, button);
        connect(button, &QToolButton::clicked, this, &startwindow::onMenuClicked);
    }
    ui->H_left->addWidget(m_leftWidget);
    ui->H_right->addWidget(m_rightWidget);
    m_whitewidget=new whitewidget;
    m_ControlModeSwitchWidget=new ControlModeSwitchWidget;
    m_Devicecontrol=new Devicecontrol;
    // m_whitewidget->show();
 //   addView(UcsDefines::UCS_VIEW_KIND_MAIN,m_whitewidget);
    buildMenu(UcsDefines::UCS_VIEW_KIND_MAIN);/*根据主页面的值设置按钮值*/

}

void startwindow::EventTriggeres(XTLevent event)
{
    if (event.eventname==UcsEventConstants::TOPCI_MENU_CLICKED)
    {
        QString name=event.m_dict.value("property").toString();
        if(name== UcsEventConstants::MENU_EVENT_LOGIN || name== UcsEventConstants::EXITTOMAIN)
        {
            m_service->changeView(UcsDefines::UCS_VIEW_KIND_MAIN);
            changeView(UcsDefines::UCS_VIEW_KIND_MAIN);
            return;
        }

        if(name== UcsEventConstants::SIM_DEVICESCONTROL)
        {
            if(SIM_DEVICECONTROL_is_shown)
            {
                m_Devicecontrol->hide();
                SIM_DEVICECONTROL_is_shown=false;
            }
            else
            {
                m_Devicecontrol->show();
                SIM_DEVICECONTROL_is_shown=true;
            }
            return;
        }
        if(name== UcsEventConstants::SIM_MISSIONPLAN)
        {
            if(SIM_Missionplan_is_shown)
            {
                situa->hide();
                SIM_Missionplan_is_shown=false;
            }
            else
            {
                situa->show();
                SIM_Missionplan_is_shown=true;
            }
            return;
        }


        if(name== UcsEventConstants::SIM_SIMULATIONINIT)
        {
            changeView(UcsDefines::SIM_SIMULATIONCONFIG);
            return;
        }
        if(name== UcsEventConstants::SIM_CONTROLMODESWITCH)
        {
            if(SIM_CONTROLMODESWITCH_is_shown)
            {
                m_ControlModeSwitchWidget->hide();
                SIM_CONTROLMODESWITCH_is_shown=false;
            }
            else
            {
                m_ControlModeSwitchWidget->show();
                SIM_CONTROLMODESWITCH_is_shown=true;
            }
            return;
        }
        if(name== UcsEventConstants::STSTEMSHUTDOWN)
        {
            QApplication::quit();
        }

    }

}

void startwindow::buildMenu(int type)
{
    clearMenu();
    switch (type)
    {
    case UcsDefines::UCS_VIEW_KIND_MAIN:
    {
        setButton(1, QStringLiteral("仿真\r\n初始化"), UcsEventConstants::SIM_SIMULATIONINIT, QString(":/b_img/star.png"));

        setButton(2, QStringLiteral("控制\r\n模式"), UcsEventConstants::SIM_CONTROLMODESWITCH, QString(":/b_img/star.png"));
        setButton(3, QStringLiteral("设备\r\n控制"), UcsEventConstants::SIM_DEVICESCONTROL, QString(":/b_img/star.png"));
        setButton(4, QStringLiteral("任务\r\n规划"), UcsEventConstants::SIM_MISSIONPLAN, QString(":/b_img/star.png"));
        setButton(12, QStringLiteral("退出"), UcsEventConstants::STSTEMSHUTDOWN, QString(":/b_img/star.png"));

        break;
    }
    case UcsDefines::SIM_SIMULATIONCONFIG:
    {
        setButton(12, QStringLiteral("返回"), UcsEventConstants::MENU_EVENT_LOGIN, QString(":/b_img/star.png"));
        break;
    }
    case UcsDefines::ROSNODEMANAGEMENT:
    {
        setButton(12, QStringLiteral("返回"), UcsEventConstants::MENU_EVENT_LOGIN, QString(":/b_img/star.png"));
        break;
    }


    default:
        break;
    }

}

void startwindow::clearMenu()
{
    QMapIterator<int, QToolButton *> i(m_buttons);
    while (i.hasNext())
    {
        i.next();
        QToolButton *button = i.value();

        button->setText("");
        button->setProperty("topic", "");
        button->setIcon(QIcon(""));
        button->setObjectName("");
    }

}

void startwindow::setButton(int index, const QString &text, const QString &topic, const QString &icon)
{
    QToolButton *button = m_buttons.value(index);
    button->setText(text);
    button->setProperty("topic", topic);
    button->setFont(QFont("Microsoft YaHei", 14, QFont::Bold));
    if (!icon.isEmpty()) {
        button->setIcon(QIcon(icon));
        button->setIconSize(QSize(49, 59));
    }
    //    button->setStyleSheet("QToolButton{padding-top:10px;margin-top:0px;}");
    button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    button->setVisible(true);

}

void startwindow::setConnectStatus(bool connectStatus)
{

}

void startwindow::setControlStatus(bool controlStatus)
{

}

void startwindow::addView(UcsDefines::UcsViewKind viewKind, QWidget *view)
{
    int i=ui->stackedWidget->count();
    widgetmap.insert(viewKind,i);
    ui->stackedWidget->addWidget(view);
}

void startwindow::changeView(UcsDefines::UcsViewKind viewKind)
{
    int i=widgetmap.value(viewKind);
    ui->stackedWidget->setCurrentIndex(i);
    buildMenu(viewKind);
}

UcsDefines::UcsViewKind startwindow::getCurrentView()
{
    //暂时没有用到的API
    return UcsDefines::UCS_VIEW_KIND_NONE;
}

void startwindow::changeMenu(const QString &oldMenu, const QString &newMenu, const QString &text)
{

}

void startwindow::changeMenu(const int num, const QString &newMenu, const QString &text)
{

}

void startwindow::onMenuClicked()
{
    QToolButton *button = dynamic_cast<QToolButton *>(sender());

    if (button->property("topic").toString().isEmpty())
        return;
    XTLevent event;
    event.eventname=   UcsEventConstants::TOPCI_MENU_CLICKED;
    event.m_dict.insert("property",button->property("topic"));
    ocu_car_manager_simActivator::postevent(event);

}
