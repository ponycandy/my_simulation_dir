#ifndef SINGLEVEHICLECARD_H
#define SINGLEVEHICLECARD_H

#include <QObject>
#include <service/UDPmessageservice.h>
#include <QTimerEvent>
#include <remote.pb.h>
// 定义摇杆数据结构体
struct JoystickData {
    double throttle = 0.0; // 油门值 [-1, 1]
    double steering = 0.0; // 转向值 [-1, 1]   HMI接口
};

// 定义摇杆数据结构体
struct ChasssisState {
    double throttle = 0.0; // 油门值 [-1, 1]
    double steering = 0.0; // 转向值 [-1, 1]   HMI接口
};



class SingleVehicleCard : public QObject
{
    Q_OBJECT
public:
    explicit SingleVehicleCard(QObject *parent = nullptr);
    void setupconnection();
    void readJoystickData();
    void WriteControlInfo();
    void sendControlMessage();
    void timerEvent(QTimerEvent *event) override;
    void disconnect();
    void connectall();
    void initialization();
    void setNet(UDPmessageservice *client,
                QString port,QString host);
    void send(QByteArray data,QString topic_name);
    int vehiclenumber;
    QString vehiclename;
    QString videoAddress;
    QString cilentID_S;
    QString host_S;
    QString port_S;
    QString username_S;
    QString password_S;
    QHostAddress adr;
    UDPmessageservice *client;
    int m_timer_1;
    bool connection_status=false;
#ifdef linux
    JoystickData joystick_data_;
    ChasssisState chasssis_state_;
    remote::v2xclient::proto::RemoteControlMsg msg_send_; // 定义为成员变量
    remote::v2xclient::proto::RemoteControlMsg msg_receive_; // 定义为成员变量
#endif
signals:

private slots:


    void onConnected();
    void onReceived(const QByteArray& message);
};

#endif // SINGLEVEHICLECARD_H
