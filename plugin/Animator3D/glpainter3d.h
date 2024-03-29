#ifndef GLPAINTER3D_H
#define GLPAINTER3D_H

#pragma once

#include "glwidget3d.h"
#include <QObject>
#include <QPainter>
#include "QPaintEvent"
#include "base_widget.h"
#include <QTimer>
#include "QGridLayout"
#include "service/Animateservice3Dservice.h"
class glwidget3D;
class base_widget;
class glpainter3D: public QObject,public Animateservice3Dservice//，这个移植到osgi框架下再说
{
    Q_OBJECT
public:
    explicit glpainter3D(QObject *parent = nullptr);
    void setupUI();
    void Draw_Camera(std::string buffer_name) override;
    void Set_Frame_world() override;//设置右x上z前y的世界坐标系到viewporjectionmatrix里面
    void Set_Frame_Camera() override;//设置右x下y前z的摄像机坐标到iewporjectionmatrix里面
    void Add_Camera(Eigen::MatrixXd &Trans,float scale,std::string buffer_name) override;
    void Create_Buffer(std::string buffer_name) override;
    void Draw_Triangular(std::string buffername) override;
    void Push_Data2buffer(std::string buffer_name,std::vector<float> data) override;
    void setbackgroundColor(float R,float G,float B,float A) override;
    void SetModelmat(glm::mat4 &Model) override;
    void GLBufferSubData(unsigned int target, ptrdiff_t offset, ptrdiff_t size, const void* data) override;
    void SetPainterID(unsigned int programID);
    void get_mouse_pos(int x, int y);
    void GLUniformMatrix4fv(int MatrixID, int count, unsigned char transpose, const float* value) override;
    void GLUseProgram(unsigned int programID) override;
    unsigned int GLGetUniformLocation(unsigned int programID, const char* name) override;
    void GLVertexAttribPointer(unsigned int indx, int size, unsigned int type, unsigned char normalized, int stride, const void* ptr) override;
    void GLBufferData(unsigned int target, ptrdiff_t size, const void* data, unsigned int usage) override;
    void GLGenBuffers(int num,unsigned int *buf) override;
    void setCameraPOS(float x,float y,float z) override;
    void GLBindBuffer(unsigned int target,unsigned int buffer) override;
    void drawcube(float Dx,float Dy,float Dz,
                  float centerx,float centery,float centerz,
                  float alpha,float beta,float gama) override;
    void drawcamera(float Dx,float Dy,float Dz,
                    float centerx,float centery,float centerz,
                    float alpha,float beta,float gama) override;
    void drawcamera_Iterate(float Dx,float Dy,float Dz,
                            float centerx,float centery,float centerz,
                            float alpha,float beta,float gama) override;

    void resizeWindow(int width,int height) override;
    void GLDrawArrays(unsigned int glmode,  int start,  int length) override;
    void setCameraParms(float nearP,float farP,float LinearSpeed=3.0f,float RotSpeed=0.0005f) override;
    void start_animate() override;
    void stop_animate() override;
    unsigned int LoadShaders(const char* vertex_file_path, const char* fragment_file_path) override;
    void register_painter(Drawer3D *painter) override;
    void GLEnableVertexAttribArray(int index) override;
    Animateservice3Dservice* cloneservice() override;
    QWidget *getwidget() override;
    void paint();
    void initialization();
    void zoomin();
    void zoomout();
    void calc_bounder();
    void moveup();
    void movedown();
    void moveright();
    void moveleft();
    void movein();
    void moveout();
    void rotateCams(int x,int y);
    void record_pressed_mouse(int x,int y);
    base_widget *m_widget;
    glwidget3D *m_glwidget;
    QTimer *timer;
    QGridLayout *layout;
    QBrush background;

    int mousex;
    int mousey;
    double recorded_mouse_x;
    double recorded_mouse_y;
    double factorin;
    double pixel_per_meter;
    double x_min;
    double y_min;
    double x_max;
    double y_max;
    double close_x=0;
    double close_y=0;
    int mouse_is_pressed;
    int m_width;
    int operation_num;
    int m_height;

    QMap<int,Drawer3D*>    DrawOperation_map;
    QMap<std::string,unsigned int> name_2_buffermap;
    QMap<std::string,std::shared_ptr<std::vector<float>>> name_2_datamap;

};

#endif // GLPAINTER3D_H
