#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include "QWidget"
#include "QSerialPort"
#include "jetsonnanoDATA/jetsonnanoDATA.h"
#include "service/eventservice.h"
#include "nlink_linktrack_anchorframe0.h"

#include "qtimer.h"
class Device_manager:public QWidget
{
    Q_OBJECT
public:
    explicit Device_manager(QWidget *parent = nullptr);
    ~Device_manager();

    void setupsensor();

    void setupcontroller();
    void setupconnection();
    void UWB_datacallback(const std::string &data);
    void processData();
    int counter=0;
    int vehiclenum;
    QSerialPort *serialPort;
    nlt_anchorframe0_t *results;

    QByteArray buffer;
    bool is_start_pos_flag=false;
    QTimer *timer;
signals:
    void sig_UWB(int rID, float head_x, float head_y, float tail_x, float tail_y);
public slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);
    void spinonce();
    void initall();
};

#endif // DEVICE_MANAGER_H
