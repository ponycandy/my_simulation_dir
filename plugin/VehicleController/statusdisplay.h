#ifndef STATUSDISPLAY_H
#define STATUSDISPLAY_H

#include <QFrame>
#include <QLabel>
class StatusDisplay : public QFrame
{
    Q_OBJECT
public:
    QString textcolor;
    StatusDisplay();
    QLabel *linear_velocity;
    QLabel *angular_velocity;
    QLabel *latitude;
    QLabel *longitude;
    QLabel *altitude;
    QLabel *BatteryHealthy;
    QLabel *BatteryTemprature;
    QLabel *motorRPM_1;
    QLabel *motorRPM_2;
    QLabel *motorRPM_3;
    QLabel *motorRPM_4;
    QLabel *acc_x;
    QLabel *acc_y;
    QLabel *acc_z;
    QLabel *roll;
    QLabel *pitch;
    QLabel *yaw;
public slots:
    void update_linear_velocity(double value);
    void update_angular_velocity(double value);
    void update_latitude(double value);
    void update_longitude(double value);
    void update_altitude(double value);
    void update_BatteryHealthy(double value);
    void update_BatteryTemprature(double value);
    void update_motorRPM_1(double value);
    void update_motorRPM_2(double value);
    void update_motorRPM_3(double value);
    void update_motorRPM_4(double value);
    void update_acc_x(double value);
    void update_acc_y(double value);
    void update_acc_z(double value);
    void update_roll(double value);
    void update_pitch(double value);
    void update_yaw(double value);
};

#endif // STATUSDISPLAY_H
