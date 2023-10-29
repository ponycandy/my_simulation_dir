#ifndef CUBEDRAWER_H
#define CUBEDRAWER_H

#include "GL_3D/Drawer3D.h"
class cubedrawer:public Drawer3D
{
public:
    cubedrawer();
    void draw() override;
};

#endif // CUBEDRAWER_H
