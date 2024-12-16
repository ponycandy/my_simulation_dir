#include "platformmanager.h"

#include <QXmlStreamReader>
#include <QIODevice>
#include <QDebug>
#include <vector>
#include <QFile>
#include <QTimerEvent>
PlatformManager::PlatformManager(QObject *parent) : QObject(parent)
{
    initplatforms();
    initprotcol();
    controlwidget=new platformsControl;
    statetranstimer=startTimer(1000);
    eventtime=0;
    controlwidget->show();
}

void PlatformManager::initplatforms()
{
    //原则是减少通信环节，尽量匹配201的DDS框架
    //所以平台就内置了，开关也留在里面
    mlvdai=new Lvdai;mlvdai->genID=0;
    platforms.insert("履带",mlvdai);
    mlunshi=new Lunshi;mlunshi->genID=0;
    platforms.insert("轮式",mlunshi);
    mliangqi = new Liangqi;mliangqi->genID=0;
    platforms.insert("两栖",mliangqi);
    mwrj=new Wrj;mwrj->genID=1;
    platforms.insert("无人机",mwrj);
    mdianzi=new Dianziduikang;mdianzi->genID=2;
    platforms.insert("电子对抗平台",mdianzi);
    msaolei=new Saoleipozhang;msaolei->genID=2;
    platforms.insert("扫雷破障平台",msaolei);
    mzhoushi=new ZhoushiJing;mzhoushi->genID=2;
    platforms.insert("周视镜",mzhoushi);
}

void PlatformManager::initprotcol()
{
    for (QMap<QString, GeneralPlatform*>::iterator it = platforms.begin(); it != platforms.end(); ++it)
    {
        it.value()->FeedBack=parseConfig(it.key() + QString("反馈接口.xml"));
        it.value()->controlport=parseConfig(it.key() + QString("控制接口.xml"));
    }
}

QVector<ProtcolUnit> PlatformManager::parseConfig(const QString &configFilePath)
{
    QXmlStreamReader reader;
    QFile file(configFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Failed to open configuration file";
        exit(1);
    }
    reader.setDevice(&file);

    QVector<ProtcolUnit> packet;
    while (!reader.atEnd() && !reader.hasError()) {
        reader.readNext();
        ProtcolUnit section;
        if (reader.isStartElement() && reader.name() == "data") {
            QString type = reader.attributes().value("type").toString();
            if (type == "uint8_t") {
                // 假设每个uint8_t占用1个字节
                section.data_8 = reader.readElementText().toUInt();
                section.Characteristicnumber=1;
                packet.push_back(section);
            }
        }
    }

    file.close();
    return packet;
    //xml文件实例:
    //    <?xml version="1.0" encoding="UTF-8"?>
    //    <configuration>
    //        <data type="uint8_t">10</data>
    //        <data type="uint8_t">20</data>
    //        <data type="uint8_t">30</data>
    //    </configuration>
}

void PlatformManager::SetplatformControl(QString platformID, ControlCommand control, ManipulateState states, EnviromentChange change)
{

}

void PlatformManager::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==statetranstimer)
    {
        eventtime++;
    };

    for (QMap<QString, GeneralPlatform*>::iterator it = platforms.begin(); it != platforms.end(); ++it)
    {
        GeneralPlatform* platform=it.value();
        FeedBackState state=platform->StateTransition(ControlCommandchache.value(it.key()),
                                  ManipulateStatechache.value(it.key()),
                                  EnviromentChangechache.value(it.key()));
        platform->broadcast(state);
    }
    ControlCommandchache.clear();
    ManipulateStatechache.clear();
    EnviromentChangechache.clear();

}
