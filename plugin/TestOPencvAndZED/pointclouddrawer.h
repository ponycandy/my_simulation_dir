#ifndef POINTCLOUDDRAWER_H
#define POINTCLOUDDRAWER_H


#include "GL_3D/Drawer3D.h"

#include <QOpenGLFunctions>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "opencv2/calib3d.hpp"
#include "sl/Camera.hpp"


class PointClouddrawer:public Drawer3D
{
public:
    PointClouddrawer();
    void draw() override;
    void initialization() override;
    GLuint programID;
    GLuint vertexcolorbuffer;
    GLuint vertexbuffer;
    sl::Camera *zed;
    GLfloat vertex[720 * 1280 * 3];
    GLfloat vertexcolor[720 * 1280 * 3];

};

#endif // POINTCLOUDDRAWER_H
