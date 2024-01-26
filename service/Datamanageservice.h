
#ifndef DATAMANAGESERVICE_H
#define DATAMANAGESERVICE_H

#include <QObject>

class Datamanageservice
{
public:
    virtual ~Datamanageservice(){}
#ifdef __linux__
    //API for linux
    virtual void store(const sensor_msgs::PointCloud data)=0;
    virtual void store(const sensor_msgs::Joy data)=0;
    virtual geometry_msgs::Twist send()=0;
    virtual void publishtocloud()=0;
    virtual char* copy_buffer(QByteArray data)=0;
    virtual void Demux(char* input)=0;
#elif _WIN32
    // windows code goes here
  //  virtual void store(const sensor_msgs::PointCloud data)=0;//创建点云数据结构
    //创建控制器控制变量结构
    //virtual void store(const sensor_msgs::Joy data)=0;
   // virtual geometry_msgs::Twist send()=0;
    virtual void publishtocloud()=0;
    virtual char* copy_buffer(QByteArray data)=0;
    virtual void Demux(char* input)=0;
#else
#endif
};
#define Datamanageservice_iid "Datamanageservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(Datamanageservice,Datamanageservice_iid  )
QT_END_NAMESPACE
#endif

