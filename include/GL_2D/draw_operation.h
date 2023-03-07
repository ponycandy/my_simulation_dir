#ifndef DRAWOPERATION_H
#define DRAWOPERATION_H

#include <QObject>
#include <QString>
#include <service/Animateservice.h>
class Animateservice;
class DrawOperation
{
public:


    virtual ~DrawOperation(){}
    virtual void draw() = 0;
    Animateservice *m_animator;
};

#endif 

