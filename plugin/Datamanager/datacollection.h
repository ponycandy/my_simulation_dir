#ifndef DATACOLLECTION_H
#define DATACOLLECTION_H
#include <mutexobj.h>
#include <QByteArray>
#ifdef __linux__
#include <geometry_msgs/Twist.h>
#endif
class Datacollection:public mutexobj
{
public:
    Datacollection();
    void set_local_cmd(double omega, double linear_speed);
    #ifdef __linux__
    geometry_msgs::Twist send_local_cmd();
    #endif
    double local_cmd[2];
};

#endif // DATACOLLECTION_H
