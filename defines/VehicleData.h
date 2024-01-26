#pragma once
//do not declare pragma pack(1) here
//it will cause system crash
//do remember that pragma pack(4) is in default
#include <stdint.h>
#include <QVector>
#include <QMap>
#include <QDateTime>
#include <QObject>
#include <QColor>
#include <QPointF>
#include <QString>
#include <QImage>
#include <QSharedPointer>
namespace  IMAGE_DATA{

typedef struct _IMAGEDATA{
    uint32_t sec;
    uint32_t nsec;
    QSharedPointer<QImage> sp_t_image;
}_IMAGEDATA;
}
namespace V1DATA {
typedef  enum{
    NORMAL,
    EXCEPTION,
    WARNING_,
}vehicle_state;
typedef  enum{
    stop,
    remote,
    remote_automatation,
    automatation,
}control_mode;
typedef  enum{
    videoenable,
    videodisable,
}video_enable;
typedef  enum{
    lidarenable,
    lidardisable,
}lidar_enable;
typedef  enum{
    camera_state_turnon,
    camera_state_turnoff,
}camera_state;

typedef  struct _ROSTIMESTAMP{
    quint32     secs;
    quint32     nsecs;
}ROSTIMESTAMP;


/**
 *
 **/
typedef  struct   _LOCATIONINFO{
    double   longtitude;
    double   latitude;
    double   altitude;
    char      stitelite;
}LOCATIONINFO;
typedef  struct   _IMUDATA{
//    w a aw v
    float wx;
    float wy;
    float wz;
    float ax;
    float ay;
    float az;
    float awx;
    float awy;
    float awz;
    float vx;
    float vy;
    float vz;
}IMUDATA;
typedef  struct   _METAELEMENT4{
    float motor1;
    float motor2;
    float motor3;
    float motor4;
}METAELEMENT4;
typedef  struct   _SINGEPOINTDATA{
    float x;
    float y;
    float intensity;
    float timestamp;

}SINGEPOINTDATA;
typedef  struct   _ORIENTATION{
    long double  x;
    long double  y;
    long double  z;
    long double  w;
}ORIENTATION;
typedef  struct   _MOTORSTATE{

     METAELEMENT4 rpm;
     METAELEMENT4 current;
     METAELEMENT4 temperture;

}MOTORSTATE;
#pragma pack(push,1)
typedef  struct   _POINTCLOUD{
    short header;
    uint32_t secquense;
    ROSTIMESTAMP time;
    uint32_t pointnum;
    QVector<SINGEPOINTDATA> point_group;
}POINTCLOUD;
#pragma pack(pop)
#pragma pack(push,1)
typedef  struct   _LASER_SCAN{
    short header;
    uint32_t secquense;
    ROSTIMESTAMP time;
    uint32_t pointnum;
    QVector<SINGEPOINTDATA> point_group;
}LASER_SCAN;
#pragma pack(pop)
typedef  struct   _SHARED_POINTCLOUD{
    QSharedPointer<POINTCLOUD> SH_POINTCLOUD;
}SHARED_POINTCLOUD;
typedef  struct   _TFTRANS{
    uint32_t secquense;
    ROSTIMESTAMP time;
    long double x;
    long double  y;
    long double  z;
    ORIENTATION orien;
}TFTRANS;
typedef  struct   _DOWNSTREAM_INFO{
    short   header;
    vehicle_state   m_state;
    control_mode   m_mode;
    float   electric_left;
    float   omega_chasis;
    float   lin_chasis;
    IMUDATA imu_data;
    MOTORSTATE motor_state;
    uint32_t left_odom;
    uint32_t right_odom;
    POINTCLOUD m_cloud;
    TFTRANS m_trans;
    LOCATIONINFO m_location;
    video_enable m_video_enable;
    lidar_enable m_lidar_enable;
    camera_state m_camera_state;
}DOWNSTREAM_INFO;
typedef  struct   _DOWNSTREAM_INFO_ISSUED{
    short   header;
    vehicle_state   m_state;
    control_mode   m_mode;
    float   electric_left;
    float   omega_chasis;
    float   lin_chasis;
    IMUDATA imu_data;
    MOTORSTATE motor_state;
    uint32_t left_odom;
    uint32_t right_odom;
    POINTCLOUD m_cloud;
    TFTRANS m_trans;
    LOCATIONINFO m_location;
    video_enable m_video_enable;
    lidar_enable m_lidar_enable;
    camera_state m_camera_state;
}DOWNSTREAM_INFO_ISSUED;
typedef  struct   _USED_DATA{
    vehicle_state   m_state;
    control_mode   m_mode;
    float   electric_left;
    float   omega_chasis;
    float   lin_chasis;
    IMUDATA imu_data;
    MOTORSTATE motor_state;
    uint32_t left_odom;
    uint32_t right_odom;
    POINTCLOUD m_cloud;
    TFTRANS m_trans;
    LOCATIONINFO m_location;
    video_enable m_video_enable;
    lidar_enable m_lidar_enable;
    camera_state m_camera_state;
}USED_DATA;
#pragma pack(push,1)
typedef  struct   _PLUSED_SWITCH_DATA{
    short   header;
    control_mode   m_mode;
}PLUSED_SWITCH_DATA;
#pragma pack(pop)
#pragma pack(push,1)
typedef  struct   _MOTIONCOMMAND{
    short   header;
    double linear;
    double angular;
}MOTIONCOMMAND;
#pragma pack(pop)
}
Q_DECLARE_METATYPE(V1DATA::POINTCLOUD);
Q_DECLARE_METATYPE(V1DATA::ROSTIMESTAMP);
Q_DECLARE_METATYPE(V1DATA::SINGEPOINTDATA);
Q_DECLARE_METATYPE(V1DATA::LOCATIONINFO);
Q_DECLARE_METATYPE(V1DATA::IMUDATA);
Q_DECLARE_METATYPE(V1DATA::PLUSED_SWITCH_DATA);
Q_DECLARE_METATYPE(V1DATA::MOTIONCOMMAND);
Q_DECLARE_METATYPE(IMAGE_DATA::_IMAGEDATA);


