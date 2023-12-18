#ifndef SLAM_DRAWER_H
#define SLAM_DRAWER_H

#include "GL_3D/Drawer3D.h"
#include <QOpenGLFunctions>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "controlpanel.h"
#include <QObject>
//先测试一下subdata的用法吧，按一下添加一个立方体
//然后，主函数里面只需要写draw_cube而不需要draw_cube_iterate
//这是比较节约内存的方法

static const float cubebuffer[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f ,//后面是补充的三个顶点

};

class Slam_Drawer : public QObject,public Drawer3D
{
    Q_OBJECT
public:
    explicit Slam_Drawer(QObject *parent = nullptr);
    void draw() override;
    void initialization() override;
    int programID;
    GLuint vbo;
    ControlPanel *panel;
    int counter=1;
    int current_buffer_size=0;
signals:

private slots:
    void addoneslot();

};

#endif // SLAM_DRAWER_H
