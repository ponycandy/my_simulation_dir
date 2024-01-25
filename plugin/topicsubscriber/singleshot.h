#ifndef SINGLESHOT_H
#define SINGLESHOT_H

#include <QObject>
#ifdef __linux__
#include <ros/ros.h>
#endif

class Singleshot : public QObject
{
    Q_OBJECT

public:
    explicit Singleshot(QObject *parent = nullptr);

#ifdef __linux__
    ros::NodeHandlePtr nh_;
    ros::Publisher pub_1;
#endif
signals:

};

#endif // SINGLESHOT_H
