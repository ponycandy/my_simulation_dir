#ifndef GL3DCOMMON_H
#define GL3DCOMMON_H
#include "sl/Camera.hpp"
#include "sl/Fusion.hpp"
#include "opencv2/opencv.hpp"
static const float g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};
// One color for each vertex. They were generated randomly.
static const float g_color_buffer_data[] = {
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
    -2.2f, 2.0f, 2.0f,
    1.4f, 1.6f, 1.0f,
    -1.2f, 1.0f, 1.4f,
};

static const float cubebuffer_vec4[] = {
    -1.0f,-1.0f,-1.0f,0.8f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,0.8f,
    -1.0f, 1.0f, 1.0f,0.8f, // triangle 1 : end
    NAN, NAN,NAN,0.8f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,0.8f,
     -1.0f, 1.0f,-1.0f,0.8f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,0.8f,
    -1.0f,-1.0f,-1.0f,0.8f,
    1.0f,-1.0f,-1.0f,0.8f,
    1.0f, 1.0f,-1.0f,0.8f,
    1.0f,-1.0f,-1.0f,0.8f,
    -1.0f,-1.0f,-1.0f,0.8f,
    -1.0f,-1.0f,-1.0f,0.8f,
    -1.0f, 1.0f, 1.0f,0.8f,
    -1.0f, 1.0f,-1.0f,0.8f,
    1.0f,-1.0f, 1.0f,0.8f,
    -1.0f,-1.0f, 1.0f,0.8f,
    -1.0f,-1.0f,-1.0f,0.8f,
    -1.0f, 1.0f, 1.0f,0.8f,
    -1.0f,-1.0f, 1.0f,0.8f,
    1.0f,-1.0f, 1.0f,0.8f,
    1.0f, 1.0f, 1.0f,0.8f,
    1.0f,-1.0f,-1.0f,0.8f,
    1.0f, 1.0f,-1.0f,0.8f,
    1.0f,-1.0f,-1.0f,0.8f,
    1.0f, 1.0f, 1.0f,0.8f,
    1.0f,-1.0f, 1.0f,0.8f,
    1.0f, 1.0f, 1.0f,0.8f,
    1.0f, 1.0f,-1.0f,0.8f,
    -1.0f, 1.0f,-1.0f,0.8f,
    1.0f, 1.0f, 1.0f,0.8f,
    -1.0f, 1.0f,-1.0f,0.8f,
    -1.0f, 1.0f, 1.0f,0.8f,
    1.0f, 1.0f, 1.0f,0.8f,
    -1.0f, 1.0f, 1.0f,0.8f,
    1.0f,-1.0f, 1.0f ,0.8f
};

inline cv::Mat slMat2cvMat(sl::Mat& input);
inline int getOCVtype(sl::MAT_TYPE type);

inline cv::Mat slMat2cvMat(sl::Mat& input)
{
    // Since cv::Mat data requires a uchar* pointer, we get the uchar1 pointer from sl::Mat (getPtr<T>())
    // cv::Mat and sl::Mat will share a single memory structure
    return cv::Mat(input.getHeight(),
                   input.getWidth(), getOCVtype(input.getDataType()),
                   input.getPtr<sl::uchar1>(sl::MEM::CPU),
                   input.getStepBytes(sl::MEM::CPU));
}
inline int getOCVtype(sl::MAT_TYPE type)
{
    int cv_type = -1;
    switch (type) {
    case sl::MAT_TYPE::F32_C1: cv_type = CV_32FC1; break;
    case sl::MAT_TYPE::F32_C2: cv_type = CV_32FC2; break;
    case sl::MAT_TYPE::F32_C3: cv_type = CV_32FC3; break;
    case sl::MAT_TYPE::F32_C4: cv_type = CV_32FC4; break;
    case sl::MAT_TYPE::U8_C1: cv_type = CV_8UC1; break;
    case sl::MAT_TYPE::U8_C2: cv_type = CV_8UC2; break;
    case sl::MAT_TYPE::U8_C3: cv_type = CV_8UC3; break;
    case sl::MAT_TYPE::U8_C4: cv_type = CV_8UC4; break;
    default: break;
    }
    return cv_type;
}
#endif 

