#ifndef WRJ_H
#define WRJ_H

#include <QObject>
#include "generalplatform.h"
class Wrj : public QObject,public GeneralPlatform
{
    Q_OBJECT
public:
    explicit Wrj(QObject *parent = nullptr);

signals:

};

#endif // WRJ_H
