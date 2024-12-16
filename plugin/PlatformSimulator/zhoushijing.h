#ifndef ZHOUSHIJING_H
#define ZHOUSHIJING_H

#include <QObject>
#include "generalplatform.h"
class ZhoushiJing : public QObject,public GeneralPlatform
{
    Q_OBJECT
public:
    explicit ZhoushiJing(QObject *parent = nullptr);

signals:

};

#endif // ZHOUSHIJING_H
