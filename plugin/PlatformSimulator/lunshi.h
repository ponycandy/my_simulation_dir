#ifndef LUNSHI_H
#define LUNSHI_H

#include <QObject>
#include "generalplatform.h"
class Lunshi : public QObject,public GeneralPlatform
{
    Q_OBJECT
public:
    explicit Lunshi(QObject *parent = nullptr);

signals:

};

#endif // LUNSHI_H
