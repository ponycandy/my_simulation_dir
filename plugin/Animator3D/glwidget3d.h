#ifndef GLWIDGET3D_H
#define GLWIDGET3D_H

#pragma once

#include <windows.h>//没有这个绝对不行！！
#include <qobject.h>
#include <QOpenGLWidget>
#include <glpainter3d.h>
#include <QTimer>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
 #include <QOpenGLVertexArrayObject>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

#include <sstream>
#include <iostream>
#include "qopenglshaderprogram.h"

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};
// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f,//后面是补充的三个顶点
    0.2f, 0.0f, 0.0f,
    0.4f, 0.6f, 0.0f,
    0.2f, 0.0f, 0.4f,
};
static const GLfloat cubebuffer[] = {
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
    -2.2f, 2.0f, 2.0f,
    1.4f, 1.6f, 1.0f,
    -1.2f, 1.0f, 1.4f,
};

class glpainter3D;
class glwidget3D: public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT

public:
    glwidget3D(QWidget *parent);
    void set_glpainter(glpainter3D *m_paint);
    void resizeGLwidget(int w,int h);
    void mouseMoveEvent(QMouseEvent *event) override;
    GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
public slots:
    void animate();

protected:
//    void paintEvent(QPaintEvent *event) override;
    void initializeGL()override;
    void resizeGL(int, int) override;
    void paintGL() override;
private:
    int elapsed;
    glpainter3D *m_painter;
    int m_width;
    int m_height;
    QOpenGLVertexArrayObject *vao;// 所谓的VAO，就是openGL例子里面，我写的就是要创建出来即使后面没什么用
    GLuint programID; //这个全局都要用
    //除掉vao的创建需要借助Qt wrapper外，其余的部分都可以用纯openGL解决掉了
};


#endif // GLWIDGET3D_H
