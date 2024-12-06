#ifndef SIMULATIONCONFIGURATION_H
#define SIMULATIONCONFIGURATION_H
#include <QWidget>
#include <QFrame>
#include <QComboBox>
#include <QPushButton>
#include <service/TCPserverservice.h>
#include <service/ocu_sim_carmanager_communicateservice.h>
#include <QDateTimeEdit>
#include "include/OCU_simulator_project/Protocol.h"

class simulationconfiguration: public QWidget,public ocu_sim_carmanager_communicateservice
{
    Q_OBJECT
public:
    explicit simulationconfiguration(QWidget *parent = nullptr);
    void setupUI();
    void send_motion_command(double linear,double omega) override;
    void send_Chasis_command(double linear,double omega) override;
    void sim_init() override;

    void setupConnection();
    void getData(QByteArray data);
    QDateTimeEdit *startTimeEdit;
//    ChasisManipulation m_chasiscontrol;

    QDateTimeEdit *endTimeEdit;
    QPushButton *startlabel;
    QPushButton *endLabel;


    TCPserverservice *m_decode;
    QFrame *comboxframe;
    QComboBox *comboBox_wheather_option;
    QComboBox *comboBox_world_option;
    QComboBox *comboBox_vehicle_option;
    QComboBox *comboBox_Mission_option;
    QPushButton *wheather_option_label;
    QPushButton *world_option_label;
    QPushButton *vehicle_option_label;
    QPushButton *Mission_option_label;
    QPushButton *Check;

    QVector<QString> weatherType;
    QVector<QString> worldType;
     QVector<QString> vehicleType;
    QVector<QString> missoinType;

     char cmd_cache[200];
    char Init_cache[1600];
     char chasis_cache[1600];

private slots:
    void On_startsimulation();
    void slot_updateControlmode(short mode,double value);
    void slot_update_chasis_state_mode(int workload_enable,int chasis_enable,int weapon_enable);

private:
};

#endif // SIMULATIONCONFIGURATION_H
