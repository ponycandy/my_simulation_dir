#ifndef TESTCUDA_H
#define TESTCUDA_H

#include "GL_3D/Drawer3D.h"
#include "cubedrawer.h"
#include <QOpenGLFunctions>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "opencv2/calib3d.hpp"
#include "sl/Camera.hpp"


#include <cuda.h>
#include <cuda_gl_interop.h>

class TestCuda:public Drawer3D
{
public:
    TestCuda();
    void draw() override;
    void initialization() override;
    GLuint programID;
    //首先，我们需要创建cuda的buffer，其地位等效于glbuffer或者vertexbuffer
    //当然，此处是指针，内容和指向还没有分配：
    //这个bufferCudaID_类似于VAO无用但是必须有:
    cudaGraphicsResource* bufferCudaID_;
    size_t numBytes_;
    GLuint vertexbuffer;//OpenGL存储顶点数据所用的buffer
    //这个xyzrgbaMappedBuf_是实际干活的buffer:
    float* xyzrgbaMappedBuf_;
    //创建从摄像机获取图像的buff:
    sl::Mat matGPU_;
    //摄像机对象创建：
    sl::Camera *zed;
    //摄像机的配置参数：
    sl::Resolution res;
    CUstream strm;
};

#endif // TESTCUDA_H
