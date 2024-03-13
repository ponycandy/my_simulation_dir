#include "simulationconfiguration.h"
#include "ocu_car_manager_simActivator.h"
#include "QDialog"
#include "qlabel.h"
#include "QMessageBox"
simulationconfiguration::simulationconfiguration(QWidget *parent) :
    QWidget(parent)
{
    setupUI();
    ocu_car_manager_simActivator::subscribeslot(this,SLOT(slot_updateControlmode(short,double)),"OCU_SIM_CONTROLMODE_UPDATE",Qt::QueuedConnection);
    ocu_car_manager_simActivator::subscribeslot(this,SLOT(slot_update_chasis_state_mode(int,int,int)),"OCU_SIM_CHASISDEVICESTATE_UPDATE",Qt::QueuedConnection);

    m_chasiscontrol.header=0xaacc;
    m_chasiscontrol.workload_enable=false;
    m_chasiscontrol.chasis_enable=false;
    m_chasiscontrol.weapon_enable=false;
    m_chasiscontrol.set_control=short(stop);
    m_chasiscontrol.speedlimit=12;
    // 初始化控制体
}

void simulationconfiguration::setupUI()
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(1680,1080);

    comboxframe=new QFrame;
    comboxframe->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    comboxframe->setAttribute(Qt::WA_TranslucentBackground);
    comboxframe->resize(500,500);
    comboxframe->setParent(this);
    comboBox_wheather_option=new QComboBox(comboxframe);
    comboBox_world_option=new QComboBox(comboxframe);
    comboBox_vehicle_option=new QComboBox(comboxframe);
    comboBox_Mission_option=new QComboBox(comboxframe);
    wheather_option_label=new QPushButton(comboxframe);
    world_option_label=new QPushButton(comboxframe);
    vehicle_option_label=new QPushButton(comboxframe);
    Mission_option_label=new QPushButton(comboxframe);
    Check=new QPushButton(comboxframe);

    wheather_option_label->setText("气象");
    world_option_label->setText("地形");
    vehicle_option_label->setText("车型");
    Mission_option_label->setText("任务");

    connect(Check,SIGNAL(clicked()),this,SLOT(On_startsimulation()));
    wheather_option_label->setGeometry(0,0,50,30);
    world_option_label->setGeometry(0,30,50,30);
    vehicle_option_label->setGeometry(0,60,50,30);
    Mission_option_label->setGeometry(0,90,50,30);

    comboBox_wheather_option->setGeometry(50,0,120,30);
    comboBox_world_option->setGeometry(50,30,120,30);
    comboBox_vehicle_option->setGeometry(50,60,120,30);
    comboBox_Mission_option->setGeometry(50,90,120,30);
    //!初始化所有选项
    weatherType.push_back("下雨");weatherType.push_back("下雪");weatherType.push_back("雾气");weatherType.push_back("雷电");weatherType.push_back("无云");
    QVector<QString>::iterator iter_weatherType;
    for (iter_weatherType=weatherType.begin();iter_weatherType!=weatherType.end();iter_weatherType++)
    {
        QString weathe=*iter_weatherType;
        comboBox_wheather_option->addItem(weathe);
    }

    worldType.push_back("丛林");worldType.push_back("海岸");worldType.push_back("山地");worldType.push_back("城市");
    QVector<QString>::iterator iter_worldType;
    for (iter_worldType=worldType.begin();iter_worldType!=worldType.end();iter_worldType++)
    {
        QString world=*iter_worldType;
        comboBox_world_option->addItem(world);
    }
    vehicleType.push_back("轻型巡逻车");vehicleType.push_back("信息电子战车");vehicleType.push_back("中型履带车");vehicleType.push_back("中型轮式车");
    QVector<QString>::iterator iter_vehicleType;
    for (iter_vehicleType=vehicleType.begin();iter_vehicleType!=vehicleType.end();iter_vehicleType++)
    {
        QString vehicle=*iter_vehicleType;
        comboBox_vehicle_option->addItem(vehicle);
    }

    missoinType.push_back("侦察");missoinType.push_back("打击");missoinType.push_back("巡逻");
    QVector<QString>::iterator iter_missoinType;
    for (iter_missoinType=missoinType.begin();iter_missoinType!=missoinType.end();iter_missoinType++)
    {
        QString missoin=*iter_missoinType;
        comboBox_Mission_option->addItem(missoin);
    }

    startlabel=new QPushButton(comboxframe);
    startlabel->setText("开始时间: ");
    startTimeEdit = new QDateTimeEdit(comboxframe);
    startTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm ");
    startTimeEdit->setDateTime(QDateTime::fromString("2000-01-01 00:30", "yyyy-MM-dd hh:mm"));

    endLabel=new QPushButton(comboxframe);
    endLabel->setText("结束时间： ");

    endTimeEdit = new QDateTimeEdit(comboxframe);
    endTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm ");
    endTimeEdit->setDateTime(QDateTime::fromString("2001-01-01 12:30", "yyyy-MM-dd hh:mm"));
    startlabel->resize(80,30);
    endLabel->resize(80,30);
    startlabel->setGeometry(0,120,80,30);
    endLabel->setGeometry(0,150,80,30);
    startTimeEdit->setGeometry(80,120,200,30);
    endTimeEdit->setGeometry(80,150,200,30);

    Check->setGeometry(0,180,170,50);
    Check->setText("确认生成仿真");
}

void simulationconfiguration::send_motion_command(double linear, double omega)
{
    MOTIONCOMMAND cmd;
    cmd.header=0xaaaa;
    cmd.angular=omega;
    cmd.linear=linear;

    QByteArray sendingdata;
    const char* ptData = cmd_cache;
    int offset,size;

    size=0;
    offset=2;
    memcpy((void *)(ptData), (void *)&cmd.header, offset);
    ptData += offset;
    size+=offset;

    offset=sizeof (cmd.linear);
    memcpy((void *)(ptData), (void *)&cmd.linear, offset);
    ptData += offset;
    size+=offset;

    offset=sizeof (cmd.angular);
    memcpy((void *)(ptData), (void *)&cmd.angular, offset);
    ptData += offset;
    size+=offset;

    sendingdata.setRawData(cmd_cache,size);

  //  m_decode->send(sendingdata);
}

void simulationconfiguration::send_Chasis_command(double linear, double omega)
{
    QByteArray sendingdata;
    const char* ptData = chasis_cache;
    int offset,size;

    size=0;
    offset=sizeof(m_chasiscontrol);
    memcpy((void *)(ptData), (void *)&m_chasiscontrol, offset);
    ptData += offset;
    size+=offset;

    sendingdata.setRawData(chasis_cache,size);

  //  m_decode->send(sendingdata);
}

void simulationconfiguration::sim_init()
{
    SimulationInit initinfoNow;
    initinfoNow.header=0xaabb;
    initinfoNow.vehicle=comboBox_vehicle_option->currentIndex();
    initinfoNow.Missionstype=comboBox_Mission_option->currentIndex();
    initinfoNow.worldtype=comboBox_world_option->currentIndex();
    initinfoNow.Weathertype=comboBox_wheather_option->currentIndex();
    TimePeriod time_period;
    QDateTime startTime = startTimeEdit->dateTime();
    time_period.starttime.year= startTime.date().year();
    time_period.starttime.month= startTime.date().month();
    time_period.starttime.days= startTime.date().daysInMonth();
    time_period.starttime.hours= startTime.time().hour();
    time_period.starttime.minite= startTime.time().minute();
    time_period.starttime.seconds= startTime.time().second();
    QDateTime endtime = endTimeEdit->dateTime();
    time_period.endingtime.year= endtime.date().year();
    time_period.endingtime.month= endtime.date().month();
    time_period.endingtime.days= endtime.date().daysInMonth();
    time_period.endingtime.hours= endtime.time().hour();
    time_period.endingtime.minite= endtime.time().minute();
    time_period.endingtime.seconds= endtime.time().second();
    initinfoNow.Missiontime=time_period;


    QByteArray sendingdata;
    const char* ptData = Init_cache;
    int offset,size;

    size=0;
    offset=2;
    memcpy((void *)(ptData), (void *)&initinfoNow.header, offset);
    ptData += offset;
    size+=offset;

    offset=sizeof (initinfoNow.vehicle);
    memcpy((void *)(ptData), (void *)&initinfoNow.vehicle, offset);
    ptData += offset;
    size+=offset;

    offset=sizeof (initinfoNow.Missionstype);
    memcpy((void *)(ptData), (void *)&initinfoNow.Missionstype, offset);
    ptData += offset;
    size+=offset;

    offset=sizeof (initinfoNow.worldtype);
    memcpy((void *)(ptData), (void *)&initinfoNow.worldtype, offset);
    ptData += offset;
    size+=offset;

    offset=sizeof (initinfoNow.Weathertype);
    memcpy((void *)(ptData), (void *)&initinfoNow.Weathertype, offset);
    ptData += offset;
    size+=offset;

    offset=sizeof (initinfoNow.Missiontime);
    memcpy((void *)(ptData), (void *)&initinfoNow.Missiontime, offset);
    ptData += offset;
    size+=offset;

    sendingdata.setRawData(Init_cache,size);

   // m_decode->send(sendingdata);
}

void simulationconfiguration::setupConnection()
{
    m_decode=ocu_car_manager_simActivator::getService<TCPserverservice>("TCPserverservice");
    m_decode=m_decode->cloneservice();
    m_decode->Bind_Slot(this,SLOT(getData(QByteArray)));

 //   m_decode->startlisten(8888);
}

void simulationconfiguration::getData(QByteArray data)
{

}

void simulationconfiguration::On_startsimulation()
{
    qDebug()<<"start_sim";

    QMessageBox msgBox;
    msgBox.setWindowTitle("仿真生成");
    msgBox.setText("提示");
    msgBox.setInformativeText("已生成仿真");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok){
        //...
    }
     QDateTime startTime = startTimeEdit->dateTime();
    qDebug()<<startTime.time().hour();
     qDebug()<<startTime.time().minute();
    qDebug()<<startTime.time().second();

}

void simulationconfiguration::slot_updateControlmode(short mode, double value)
{
    m_chasiscontrol.set_control=mode;
    m_chasiscontrol.speedlimit=value;
    send_Chasis_command(0, 0);
}

void simulationconfiguration::slot_update_chasis_state_mode(int workload_enable, int chasis_enable, int weapon_enable)
{
    m_chasiscontrol.workload_enable=workload_enable;
    m_chasiscontrol.chasis_enable=chasis_enable;
    m_chasiscontrol.weapon_enable=weapon_enable;
    send_Chasis_command(0, 0);
}
