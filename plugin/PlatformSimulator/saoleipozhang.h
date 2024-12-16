#ifndef SAOLEIPOZHANG_H
#define SAOLEIPOZHANG_H

#include <QObject>
#include "generalplatform.h"
class Saoleipozhang : public QObject,public GeneralPlatform
{
    Q_OBJECT
public:
    explicit Saoleipozhang(QObject *parent = nullptr);

signals:

};

#endif // SAOLEIPOZHANG_H
