
#ifndef ANIMATESERVICE3DSERVICE_H
#define ANIMATESERVICE3DSERVICE_H

#include <QObject>
#include <GL_3D/Drawer3D.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Eigen/core>
class Drawer3D;
class Animateservice3Dservice
{
public:
    virtual ~Animateservice3Dservice(){}
    virtual void GLBufferSubData(unsigned int target, ptrdiff_t offset, ptrdiff_t size, const void* data)=0;
    virtual void resizeWindow(int width,int height)=0;
    virtual void Draw_Triangular(std::string buffername)=0;
    virtual void Add_Camera(Eigen::MatrixXd &Trans,float scale,std::string buffer_name)=0;
    virtual void Draw_Camera(std::string buffer_name)=0;
    virtual void Set_Frame_world()=0;
    virtual void Set_Frame_Camera()=0;
    virtual void Push_Data2buffer(std::string buffer_name,std::vector<float> data)=0;
    virtual void Create_Buffer(std::string buffer_name)=0;
    virtual void setCameraParms(float nearP,float farP,float LinearSpeed=3.0f,float RotSpeed=0.0005f)=0;
    virtual void setCameraPOS(float x,float y,float z)=0;
    virtual void setbackgroundColor(float R,float G,float B,float A)=0;
    virtual void SetModelmat(glm::mat4 &Model)=0;
    virtual void SetPainterID(unsigned int programID)=0;
    virtual void GLUseProgram(unsigned int programID)=0;
    virtual unsigned int GLGetUniformLocation(unsigned int programID, const char* name)=0;
    virtual void GLUniformMatrix4fv(int MatrixID, int count, unsigned char transpose, const float* value)=0;
    virtual void start_animate()=0;
    virtual void stop_animate()=0;
    virtual void GLGenBuffers(int num,unsigned int *buf)=0;
    virtual void GLBindBuffer(unsigned int target,unsigned int buffer)=0;
    virtual void GLBufferData(unsigned int target, ptrdiff_t size, const void* data, unsigned int usage)=0;
    virtual void GLEnableVertexAttribArray(int index)=0;
    virtual void GLVertexAttribPointer(unsigned int indx, int size, unsigned int type, unsigned char normalized, int stride, const void* ptr)=0;
    virtual void register_painter(Drawer3D *painter)=0;
    virtual void GLDrawArrays(unsigned int glmode,  int start,  int length)=0;//基础函数
    virtual unsigned int LoadShaders(const char* vertex_file_path, const char* fragment_file_path)=0;
    virtual void drawcube(float Dx,float Dy,float Dz,
            float centerx,float centery,float centerz,
            float alpha,float beta,float gama)=0;
    //三个参数，长宽高，依次对应长方体的几何中心在原点时
    //沿着x,y,z方向的长度
    //然后是几何方位，这里的输入考虑直接使用glm输入？
    //毕竟glm非常擅长构建这个东西.......
    //然后是方位角的输入.....这个东西就有点儿头痛了
    //欧拉角，四元数，还是矩阵,输入欧拉角吧，我们需要几何直观
    //这里输入的坐标是实际物理坐标，不是openGL的绘图坐标
    virtual void drawcamera(float Dx,float Dy,float Dz,
                          float centerx,float centery,float centerz,
                          float alpha,float beta,float gama)=0;
    virtual void drawcamera_Iterate(float Dx,float Dy,float Dz,
                            float centerx,float centery,float centerz,
                            float alpha,float beta,float gama)=0;
    //可能的可变部分，一部分iterate(历史)，一部分实时，所以还是加一个iterate专门接口比较好
    virtual Animateservice3Dservice* cloneservice()=0;
    virtual QWidget* getwidget()=0;

};
#define Animateservice3Dservice_iid "Animateservice3Dservice"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(Animateservice3Dservice,Animateservice3Dservice_iid  )
QT_END_NAMESPACE

#endif

