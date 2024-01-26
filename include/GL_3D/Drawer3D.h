#ifndef DRAWER3D_H
#define DRAWER3D_H

#include <QObject>
#include <QString>
#include <service/Animateservice3Dservice.h>
class Animateservice3Dservice;
class Drawer3D
{
public:


    virtual ~Drawer3D(){}
    virtual void draw() = 0;
    virtual void initialization() =0;
    Animateservice3Dservice *m_animator;
};

#endif 

