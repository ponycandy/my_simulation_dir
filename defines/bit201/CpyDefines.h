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

namespace BITDefine {

#pragma pack(push,1)
typedef struct _NetHeadet
{
    int ipv4_phase_1;
    int ipv4_phase_2;
    int ipv4_phase_3;
    int ipv4_phase_4;
    int port;

    int source_ipv4_phase_1;
    int source_ipv4_phase_2;
    int source_ipv4_phase_3;
    int source_ipv4_phase_4;
    int source_port;
}NetHeadet;
#pragma pack(pop)
}


Q_DECLARE_METATYPE(BITDefine::NetHeadet);


