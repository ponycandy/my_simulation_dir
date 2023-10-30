#include "pointclouddrawer.h"
#include "GL_3D/GL3Dcommon.h"
PointClouddrawer::PointClouddrawer()
{
    // Create a ZED camera object
//    zed=new sl::Camera ;

//    // Open the camera
//    sl::ERROR_CODE returned_state = zed->open();
//    if (returned_state != sl::ERROR_CODE::SUCCESS) {
//        std::cout << "Error " << returned_state << ", exit program.\n";
//        return ;
//    }

//    // Get camera information (ZED serial number)
//    auto camera_infos = zed->getCameraInformation();
//    qDebug()<<"camera connected";
//    printf("Hello! This is my serial number: %d\n", camera_infos.serial_number);

    // Close the camera
//    zed.close();
//    sl::Mat point_cloud;
//    zed->retrieveMeasure(point_cloud, sl::MEASURE::XYZRGBA);
//    // Get the resolution of the point cloud
//    static sl::Resolution res = point_cloud.getResolution();





//    // Loop through each row
//    int i=0;
//    for (int y = 0; y < res.height; y++) {
//        // Loop through each column
//        for (int x = 0; x < res.width; x++) {
//            // Get the value of the element as a float4
//            sl::float4 point_value;
//            point_cloud.getValue(x, y, &point_value);
//            // Do something with the point value
//            // For example, print the X, Y, Z coordinates
//            //            std::cout << "Point (" << x << ", " << y << ") has coordinates: ("
//            //                      << point_value.x << ", " << point_value.y << ", " << point_value.z << ")"
//            //                      << std::endl;
//            vertex[i]=point_value.x;vertexcolor[i]=point_value.w;i++;
//            vertex[i]=point_value.y;vertexcolor[i]=point_value.w;i++;
//            vertex[i]=point_value.z;vertexcolor[i]=point_value.w;i++;
//        }
//    }
//    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//    m_animator->GLBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
//    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexcolorbuffer);
//    m_animator->GLBufferData(GL_ARRAY_BUFFER, sizeof(vertexcolor), vertexcolor, GL_STATIC_DRAW);
    //我们这里能够显示的实际上是雷达的点云....
}

void PointClouddrawer::draw()
{

    //绑定到shader里边
    m_animator->GLDrawArrays(GL_POINTS, 0, 36);

}

void PointClouddrawer::initialization()
{
    programID = m_animator->LoadShaders("vertexview.shader", "Fragcolorset.shader");
    m_animator->SetPainterID(programID);



    m_animator->GLGenBuffers(1, &vertexbuffer);
    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    m_animator->GLBufferData(GL_ARRAY_BUFFER, sizeof(cubebuffer), cubebuffer, GL_STATIC_DRAW);


    m_animator->GLGenBuffers(1, &vertexcolorbuffer);
    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexcolorbuffer);
    // 将vertex颜色数据塞进来
    m_animator->GLBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    m_animator->GLEnableVertexAttribArray(0);
    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    m_animator->GLVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, nullptr);

    m_animator->GLEnableVertexAttribArray(1);
    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexcolorbuffer);
    m_animator->GLVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0, nullptr);
    m_animator->GLUseProgram(programID);
    //矩阵塞入得放在GLUseProgram(programID)的后面！！
    //以及主循环中不允许使用GLBindBuffer和GLBufferData修改数据！！
    glm::mat4 Model = glm::mat4(1.0f);
    GLuint MatrixID = m_animator->GLGetUniformLocation(programID, "Modelmat");
    m_animator->GLUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Model[0][0]);
}
