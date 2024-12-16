#ifndef DIANZIDUIKANG_H
#define DIANZIDUIKANG_H

#include <QObject>
#include "generalplatform.h"
class Dianziduikang : public QObject,public GeneralPlatform
{
    Q_OBJECT
public:
    explicit Dianziduikang(QObject *parent = nullptr);

signals:

};

#endif // DIANZIDUIKANG_H
