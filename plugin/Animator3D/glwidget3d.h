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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class glpainter3D;
class glwidget3D: public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT

public:
    glwidget3D(QWidget *parent);
    void GLBufferSubData(unsigned int target, ptrdiff_t offset, ptrdiff_t size, const void* data);
    void SetModelmat(glm::mat4 &Model);
    void set_glpainter(glpainter3D *m_paint);
    unsigned int GLGetUniformLocation(unsigned int programID, const char* name);
    void GLUniformMatrix4fv(int MatrixID, int count, unsigned char transpose, const float* value);
    void GLUseProgram(unsigned int programID);
    void GLVertexAttribPointer(unsigned int indx, int size, unsigned int type, unsigned char normalized, int stride, const void* ptr);
    void GLEnableVertexAttribArray(int index);
    void GLBindBuffer(unsigned int target,unsigned int buffer);
    void GLBufferData(unsigned int target, ptrdiff_t size, const void* data, unsigned int usage);
    void GLGenBuffers(int num, unsigned int *buf);
    void GLDrawArrays(unsigned int glmode,  int start,  int length);
    void rotateCams(int x, int y);
    void move_in_direction(glm::vec3 direc);
    void resizeGLwidget(int w,int h);
    void mouseMoveEvent(QMouseEvent *event) override;
    GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);


    glm::mat4 ViewMatrix;
    glm::mat4 Transformworld2worldMat;
    glm::mat4 camera_frame_T;//设置右x下y前z
    glm::mat4 world_frame_T;//设置右x上z前y

    //从正交XYZ坐标（上Z右x前y）向屏幕XYZ坐标转化（上y右x后Z）
    glm::mat4 ProjectionMatrix;
    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;
    GLuint m_programID; //这个全局都要用
    float Channel_R;
    float Channel_G;
    float Channel_B;
    float Channel_A;
    float nearplanedis;
    float farplanedis;
    float speed;
    float mousespeed;
    glm::vec3 position;
    int m_width;
    int m_height;
    float FOV;
public slots:
    void animate();

protected:
    //    void paintEvent(QPaintEvent *event) override;
    void initializeGL()override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
private:
    int elapsed;
    glpainter3D *m_painter;


    QOpenGLVertexArrayObject *vao;// 所谓的VAO，就是openGL例子里面，我写的就是要创建出来即使后面没什么用


    float horizontalAngle;
    float verticalAngle;

    //除掉vao的创建需要借助Qt wrapper外，其余的部分都可以用纯openGL解决掉了
};


#endif // GLWIDGET3D_H
