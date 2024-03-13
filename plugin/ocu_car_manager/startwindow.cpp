#include "startwindow.h"
#include "ui_startwindow.h"
#include "ocu_car_managerActivator.h"
#include "event/OcuEventContants.h"
#include "qcoreapplication.h"
#ifdef __linux
#include "service/ROSnodeservice.h"
#endif
startwindow::startwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::startwindow),m_whitewidget(NULL)
{
    ui->setupUi(this);
    setupwidget();
    m_viewManager=new ViewManager;
    ocu_car_managerActivator::registerservice(this,"ocu_car_coreservice");
    m_service=ocu_car_managerActivator::getService<Coreservice>("Coreservice");
    m_service->addView(UcsDefines::UCS_VIEW_KIND_MAIN,this);
    m_service->changeView(UcsDefines::UCS_VIEW_KIND_MAIN);
    ocu_car_managerActivator::subscribevent(UcsEventConstants::TOPCI_MENU_CLICKED,this);
    //UcsEventConstants::TOPCI_MENU_CLICKED
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
    addView(UcsDefines::UCS_VIEW_KIND_MAIN,m_whitewidget);
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
        if(name== UcsEventConstants::STSTEMSHUTDOWN)
        {
#ifdef __linux__
            ROSnodeservice *m_service_ros=ocu_car_managerActivator::getService<ROSnodeservice>("ROSnodeservice");
            m_service_ros->destroyall();
            QApplication::quit();
#endif
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
        setButton(1, QStringLiteral("连接\r\n配置"), UcsEventConstants::NETCONFIG, QString(":/b_img/star.png"));

        setButton(2, QStringLiteral("切换\r\n显示"), UcsEventConstants::DISPLAYSTATUS, QString(":/b_img/star.png"));
        setButton(3, QStringLiteral("指令\r\n执行"), UcsEventConstants::COMMANDLINEEXEC, QString(":/b_img/star.png"));
        setButton(4, QStringLiteral("任务\r\n规划"), UcsEventConstants::MISSIONPLAN, QString(":/b_img/star.png"));
        setButton(5, QStringLiteral("信源\r\n切换"), UcsEventConstants::SOURCESWITCH, QString(":/b_img/star.png"));

        setButton(12, QStringLiteral("退出"), UcsEventConstants::STSTEMSHUTDOWN, QString(":/b_img/star.png"));

        break;
    }
    case UcsDefines::NETCONFIG_INTERFACE:
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
    ocu_car_managerActivator::postevent(event);

}
