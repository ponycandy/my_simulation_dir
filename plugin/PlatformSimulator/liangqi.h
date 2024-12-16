#ifndef LIANGQI_H
#define LIANGQI_H

#include <QObject>
#include "generalplatform.h"
class Liangqi : public QObject,public GeneralPlatform
{
    Q_OBJECT
public:
    explicit Liangqi(QObject *parent = nullptr);

signals:

};

#endif // LIANGQI_H
