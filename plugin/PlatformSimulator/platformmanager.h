#ifndef PLATFORMMANAGER_H
#define PLATFORMMANAGER_H

#include <QObject>
#include "lvdai.h"
#include "lunshi.h"
#include "liangqi.h"
#include "wrj.h"
#include "dianziduikang.h"
#include "saoleipozhang.h"
#include "zhoushijing.h"
#include <QMap>
#include "platformscontrol.h"
class Lvdai;//履带
class Lunshi;//轮式
class Liangqi;//两栖
class Wrj;//无人机

class Dianziduikang;//电子对抗
class Saoleipozhang;//扫雷破障
class ZhoushiJing;//周视镜

class ProtcolUnit;//协议体
class nodegrah;//通讯节点表，决定自身的插入时机
class PlatformManager : public QObject
{
    Q_OBJECT
public:
    explicit PlatformManager(QObject *parent = nullptr);
    /**
     * @brief初始化所有平台
     */
    void initplatforms();
    /**
     * @brief初始化所有协议
     */
    void initprotcol();

    QVector<ProtcolUnit> parseConfig(const QString& configFilePath);
    Lvdai *mlvdai;
    Lunshi *mlunshi;
    Liangqi *mliangqi;
    Wrj *mwrj;
    Dianziduikang *mdianzi;
    Saoleipozhang *msaolei;
    ZhoushiJing *mzhoushi;
    QMap<QString,GeneralPlatform*> platforms;
    /**
     * @brief 显示无人车状态以及模拟输入界面
     */
    platformsControl *controlwidget;
    /**
     * @brief 节点图，详见lean4中的数学建模
     */
    nodegrah *mnodelist;
    /**
     * @brief 仿真世界计时器
     */
    uint64_t eventtime;
    /**
     * @brief 主循环计时器
     */
    int statetranstimer;
    /**
     * @brief ControlCommand缓存
     */
    QMap<QString,ControlCommand> ControlCommandchache;
    /**
     * @brief ManipulateState缓存
     */
    QMap<QString,ManipulateState> ManipulateStatechache;
    /**
     * @brief EnviromentChange缓存
     */
    QMap<QString,EnviromentChange>EnviromentChangechache;
public slots:
    void SetplatformControl(QString platformID,ControlCommand control,ManipulateState states,EnviromentChange change);
signals:

private:
    /**
     * @brief 时间触发的车辆状态更新，触发车辆状态运动函数
     *
     *
     * @param param1 参数1的描述。
     * @param param2 参数2的描述。
     */
    void timerEvent(QTimerEvent *event) override;

};

#endif // PLATFORMMANAGER_H
