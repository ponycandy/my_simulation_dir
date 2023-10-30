#ifndef CUBEDRAWER_H
#define CUBEDRAWER_H

#include "GL_3D/Drawer3D.h"
#include "GL_3D/GL3Dcommon.h"
#include <QOpenGLFunctions>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "opencv2/calib3d.hpp"
#include "sl/Camera.hpp"

class cubedrawer:public Drawer3D
{
public:
    cubedrawer();
    void draw() override;
    void initialization() override;
    GLuint vertexbuffer;
    GLuint vertexcolorbuffer;
    GLuint programID;
};

#endif // CUBEDRAWER_H
