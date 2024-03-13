#include "controlwidget.h"

ControlWidget::ControlWidget(QWidget *parent)
    : QWidget{parent}
{
}

void ControlWidget::set_backgroundPannel(QWidget *pannel)
{
    m_pannel=pannel;
    initUI();
}

void ControlWidget::initUI()
{
    Background=new QFrame;
    Background->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    Background->setAttribute(Qt::WA_TranslucentBackground);
    Background->resize(1000,600);//设置覆盖在GIS模块上面
    Background->setParent(this);


    m_pannel->setParent(Background);
    m_pannel->move(0,0);

    // m_pannel->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    // m_pannel->setAttribute(Qt::WA_TranslucentBackground);
    //目前来看，不太有可能，如何计算几何地理坐标这一点，可能需要参考一些简单的方法，此处暂时空着

    this->setGeometry(100,100,1200,600);

    AddObstacle_plot=new QPushButton;
    loadConfigFile=new QPushButton;
    AddObstacle_coordinate=new QPushButton;
    Add_Target=new QPushButton;
    Add_Event=new QPushButton;

    AddObstacle_plot->setText("绘制障碍物");
    AddObstacle_plot->setParent(this);
    AddObstacle_plot->setGeometry(1000,100,180,30);

    loadConfigFile->setText("加载仿真配置文件");
    loadConfigFile->setParent(this);
    loadConfigFile->setGeometry(1000,200,180,30);

    AddObstacle_coordinate->setText("添加障碍物坐标");
    AddObstacle_coordinate->setParent(this);
    AddObstacle_coordinate->setGeometry(1000,300,180,30);

    Add_Target->setText("添加目标车辆");
    Add_Target->setParent(this);
    Add_Target->setGeometry(1000,400,180,30);

    Add_Event->setText("添加事件");
    Add_Event->setParent(this);
    Add_Event->setGeometry(1000,500,180,30);
}

void ControlWidget::startanimate()
{
    this->show();
}
