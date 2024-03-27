#include "controlwidget.h"
#include "include/FILE_manage/f_manager.h"
#include "xmlcore.h"
#include "Visualizer_201Activator.h"
#include "include/OSGIEVENT.h"
ControlWidget::ControlWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    initUI();
    m_sim=Visualizer_201Activator::getService<SwarmSimservice>("SwarmSimservice");

    qRegisterMetaType<QMap<int,SwarmAgent*>>("QMap<int,SwarmAgent*>");
    Visualizer_201Activator::subscribeslot(this,SLOT(slot_agent_state_update(QMap<int,SwarmAgent*>)),OSGIEVENT::SIG_AGENT_STATE_UPDATE,Qt::QueuedConnection);
    agents_num=-1;
    simtimer=new QTimer;
    connect(simtimer,SIGNAL(timeout()),this,SLOT(Onstepin()));


}
void ControlWidget::initUI()
{
    this->move(0,0);

    Background=new QFrame;
    Background->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    Background->setAttribute(Qt::WA_TranslucentBackground);
    Background->resize(1920,1080);//设置覆盖在GIS模块上面
    Background->setParent(this);

    quitapp=new QPushButton;
    loadConfigFile=new QPushButton;
    AddObstacle_coordinate=new QPushButton;
    stop_AddObstacle_coordinate=new QPushButton;
    Add_Event=new QPushButton;

    quitapp->setText("关闭程序");
    quitapp->setParent(Background);
    quitapp->setGeometry(1500,0,100,30);
    connect(quitapp,SIGNAL(clicked()),this,SLOT(Onshutdown()));

    loadConfigFile->setText("加载仿真文件");
    loadConfigFile->setParent(Background);
    loadConfigFile->setGeometry(1500,30,100,30);
    connect(loadConfigFile,SIGNAL(clicked()),this,SLOT(Onloadingconfig()));

    AddObstacle_coordinate->setText("圈选区域");
    AddObstacle_coordinate->setParent(Background);
    AddObstacle_coordinate->setGeometry(1500,60,100,30);
    connect(AddObstacle_coordinate,SIGNAL(clicked()),this,SLOT(OnchooseArea()));

    stop_AddObstacle_coordinate->setText("停止圈选区域");
    stop_AddObstacle_coordinate->setParent(Background);
    stop_AddObstacle_coordinate->setGeometry(1500,60,100,30);
    connect(stop_AddObstacle_coordinate,SIGNAL(clicked()),this,SLOT(OnstopchooseArea()));
    stop_AddObstacle_coordinate->hide();

    Slider_Background=new QFrame(this);
    Slider_Background->setGeometry(350,1000,1000,30);
    Slider_Background->setStyleSheet("background-color: rgba(0, 0, 255,0.1)");

    Sim_Start_stop_Label=new QPushButton(Slider_Background);
    Sim_Start_stop_Label->setGeometry(0,0,100,30);
    Sim_Start_stop_Label->setText("事件开始");
    Sim_Start_stop_Label->setStyleSheet("background-color: rgb(255, 0, 255)");
    Sim_Start_stop_Label->setFont(QFont("宋体", 18));
    connect(Sim_Start_stop_Label,SIGNAL(clicked()),this,SLOT(OnStartsimulation()));

    timeslider=new QSlider(Qt::Horizontal);
    timeslider->setParent(Slider_Background);
    timeslider->setGeometry(100,0,1000,30);
    timeslider->setMaximum(100);
    timeslider->setMinimum(0); // Set minimum value
    timeslider->setValue(0); // Set default value
    timeslider->setTickPosition(QSlider::TicksBelow); // Ticks below the slider

    Add_Event->setText("事件编辑器");
    Add_Event->setParent(this);
    Add_Event->setGeometry(1600,0,100,30);

    eventwidget=new EventEditer;
    eventwidget->move(0,0);
    eventwidget->hide();
    connect(Add_Event,SIGNAL(clicked()),this,SLOT(OnStartEventtrigger()));

}

QGeoCoordinate ControlWidget::getcoordinatefromgrid(double x, double y, QGeoCoordinate center)
{
    double temPI=3.1415926535;
    double earth_R=6356.9088;//km
    double d_theta=0.001/earth_R;//每米对应的纬度增长,单位为RAD
    double d_phi=0.001/(earth_R*cos(temPI*center.latitude()/180));//每米对应的经度增长,单位为RAD
    double lat=center.latitude();
    double log=center.longitude();
    lat+=180*y*d_theta/temPI;//修正
    log+=180*x*d_phi/temPI;

    // lat+=9.009009009009009009009009009009e-6 *y;
    // log+=1.1710973181871413514463051879611e-5 *x;

    QGeoCoordinate returnedvalue({lat,log});
    return returnedvalue;
}

void ControlWidget::Onshutdown()
{
    QApplication::quit();
}

void ControlWidget::Onloadingconfig()
{
    m_sim=m_sim->cloneservice();
    // QString filename=f_FileOpen();//先留着
    QString filename="D:/QT/prjdir/OSGIMODULE/my_simulation_dir/build/config/swarm/swarm_201.xml";
    if(filename=="")
    {

    }
    else
    {
        m_vehiclemodel=new vehicle(filename);
        m_sim->init_plant(30,filename,m_vehiclemodel);
        dynamicsimer=m_sim->get_simer();
        dynamicsimer->set_step_in_mode(1);
    }


}

void ControlWidget::OnchooseArea()
{
    stop_AddObstacle_coordinate->show();
    M_map->choosearea(QColor(0,0,125,125));
}

void ControlWidget::OnstopchooseArea()
{
    stop_AddObstacle_coordinate->hide();
    QVector<QGeoCoordinate> vertex=M_map->stopchoosearea();

    QVector<QGeoCoordinate>::Iterator vertexiter;
    int i=0;
    for (vertexiter=vertex.begin();vertexiter!=vertex.end();vertexiter++)
    {
        QGeoCoordinate corrdinate=(*vertexiter);
        qDebug()<<"标号"<<QString::number(i)<<" 纬度："<<corrdinate.latitude()<<" 经度："<<corrdinate.longitude();
        i++;
    }

}

void ControlWidget::OnStartsimulation()
{
    if(Sim_Start_stop_Label->text()=="事件开始")
    {
        Sim_Start_stop_Label->setText("暂停");
        simtimer->start(30);
    }
    else
    {
        Sim_Start_stop_Label->setText("事件开始");
        simtimer->stop();
    }
}

void ControlWidget::slot_agent_state_update(QMap<int, SwarmAgent *> agentgroup)
{
    if(agents_num==agentgroup.size())
    {
        //更新之前的代理的位置
        AgentGroup=agentgroup;
        QMapIterator<int, SwarmAgent *> itermap(AgentGroup);
        while(itermap.hasNext())
        {
            itermap.next();
            QGeoCoordinate coordinate({39.959,116.321});
            QGeoCoordinate agentcoordinate=getcoordinatefromgrid(itermap.value()->pos_xy(0,0),
                                                                   itermap.value()->pos_xy(1,0),
                                                                   coordinate);
            M_map->Update_Object_Item(itermap.key(),agentcoordinate,itermap.value()->heading_angle);
        }
        agents_num=agentgroup.size();
    }
    else
    {
        //首次代理数量变化，重置代理数量
        AgentGroup=agentgroup;
        QMapIterator<int, SwarmAgent *> itermap(AgentGroup);
        while(itermap.hasNext())
        {
            itermap.next();
            QPixmap picture(":/red.png");
            QGeoCoordinate coordinate({39.959,116.321});
            QGeoCoordinate agentcoordinate=getcoordinatefromgrid(itermap.value()->pos_xy(0,0),
                                                                   itermap.value()->pos_xy(1,0),
                                                                   coordinate);
            M_map->Add_Object_Item(itermap.key(),picture,agentcoordinate,itermap.value()->heading_angle);
        }
        agents_num=agentgroup.size();
    }
}

void ControlWidget::Onstepin()
{
    dynamicsimer->step_in();
}

void ControlWidget::OnStartEventtrigger()
{
    if(showeventediter)
    {
        eventwidget->show();
        showeventediter=false;
    }
    else
    {
        eventwidget->hide();
        showeventediter=true;
    }
}
