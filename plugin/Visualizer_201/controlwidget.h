#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include "QPushButton"
#include "QFrame"
#include "service/Mapservice.h"
#include "graphicsmap.h"
#include "interactivemap.h"
#include "QApplication"
#include "QSlider"
#include "service/SwarmSimservice.h"
#include "vehicle.h"
#include "eventediter.h"
class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief 初始化对象
     * @param parent
     * @return null
     */
    explicit ControlWidget(QWidget *parent = nullptr);
    QPushButton *quitapp;
    QSlider *timeslider;
    QPushButton *loadConfigFile;
    QPushButton *AddObstacle_coordinate;
    QPushButton *stop_AddObstacle_coordinate;
    QPushButton *Sim_Start_stop_Label;
    QPushButton *Add_Event;
    QFrame *Background;
    QFrame *Slider_Background;
    QTimer *simtimer;
    vehicle *m_vehiclemodel;
    MapService *M_map;
    SwarmSimservice *m_sim;
    SimDynamicsservice *dynamicsimer;
    int agents_num;//当前所有代理的数量
    QMap<int, SwarmAgent *> AgentGroup;
    EventEditer *eventwidget;
    bool showeventediter=false;
private:
    /**
     * @brief 初始化界面
     * @param
     * @return
     */
    void initUI();
    /**
     * @brief 将仿真器中的坐标转化为墨卡托投影地图中的坐标
     *          仿真器坐标系，x轴向东，y轴向北
     * @param x、y:仿真器中坐标 ,center:仿真器中坐标（0，0）对应的地图坐标
     * @return 转化(x,y)后的经纬度坐标
     */
    QGeoCoordinate getcoordinatefromgrid(double x,double y,QGeoCoordinate center);

signals:

private slots:
    /**
     * @brief 关闭仿真程序
     * @param
     * @return
     */
    void Onshutdown();

    /**
     * @brief 加载仿真配置文件
     * @param
     * @return
     */
    void Onloadingconfig();

    /**
     * @brief 勾选障碍物区域
     * @param
     * @return
     */
    void OnchooseArea();
    /**
     * @brief 停止勾选障碍物区域
     * @param
     * @return
     */
    void OnstopchooseArea();
    /**
     * @brief 开始或者暂停仿真
     * @param
     * @return
     */
    void OnStartsimulation();
    /**
     * @brief 绘制代理们的位置图标
     * @param
     * @return
     */
    void slot_agent_state_update(QMap<int,SwarmAgent*> agentgroup);
    /**
     * @brief 开启步进
     * @param
     * @return
     */
    void Onstepin();
    /**
     * @brief 打开事件编辑器的按钮
     * @param
     * @return
     */
    void OnStartEventtrigger();

};


#endif // CONTROLWIDGET_H
