#ifndef SITUATIONALPLAN_H
#define SITUATIONALPLAN_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
class SituationalPlan : public QWidget
{
    Q_OBJECT
public:
    explicit SituationalPlan(QWidget *parent = nullptr);
    QFrame *frame;
    QPushButton *pickpoints;//地图选点
    QPushButton *autogoback;//自动返航
    QPushButton *recordpoints;//自主录制
    QPushButton *pickpoints_check;//选点完成
    QPushButton *quitrecord;//终止录点
    QPushButton *loadtaskfile;//加载路径文件

public slots:
    void On_Send_autogoback_command();
    void On_finishpointsselection_command();
    void On_hiding_pickpoints_check_command();
    void On_startrecord_command();
    void On_hiding_quitrecord_check_command();
    void On_loadingfile_command();

signals:
};

#endif // SITUATIONALPLAN_H
