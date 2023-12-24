#include "slam_drawer.h"

Slam_Drawer::Slam_Drawer(QObject *parent)
    : QObject{parent}
{
    //panel=new ControlPanel;
    //connect(panel,SIGNAL(addone()),this,SLOT(addoneslot()));
   // panel->show();
    //current_buffer_size=sizeof(cubebuffer);
    //counter=1;

}

void Slam_Drawer::draw()
{
//    m_animator->Draw_Triangular("testcubic");
    m_animator->Draw_Camera("camera");
}

void Slam_Drawer::initialization()
{
    programID = m_animator->LoadShaders("./shaders/frequently_used_vertex.shader",
                                        "./shaders/frequently_used_frag.shader");
    m_animator->SetPainterID(programID);
    m_animator->Create_Buffer("testcubic");
    //     std::vector<float> data = {    -1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,-1.0f, 1.0f, 1.0f, // triangle 1 : end
    //                                1.0f, 1.0f,-1.0f,-1.0f,-1.0f,-1.0f, -1.0f, 1.0f,-1.0f,1.0f,-1.0f, 1.0f,
    //                                -1.0f,-1.0f,-1.0f, 1.0f,-1.0f,-1.0f,1.0f, 1.0f,-1.0f, 1.0f,-1.0f,-1.0f,
    //                                -1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f, -1.0f, 1.0f, 1.0f,-1.0f, 1.0f,-1.0f,1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f,
    //                                -1.0f,-1.0f,-1.0f, -1.0f, 1.0f, 1.0f,-1.0f,-1.0f, 1.0f,1.0f,-1.0f, 1.0f,
    //                                1.0f, 1.0f, 1.0f,1.0f,-1.0f,-1.0f,1.0f, 1.0f,-1.0f,1.0f,-1.0f,-1.0f,1.0f, 1.0f, 1.0f,1.0f,-1.0f, 1.0f, 1.0f, 1.0f, 1.0f,1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,
    //                                1.0f, 1.0f, 1.0f,-1.0f, 1.0f,-1.0f,-1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f,-1.0f, 1.0f, 1.0f,1.0f,-1.0f, 1.0f};

//    std::vector<float> data = {0,0,0,
//                               1,0,0,
//                               0.5,1,0};
//    m_animator->Push_Data2buffer("testcubic",data);
    m_animator->Set_Frame_world();
    m_animator->Create_Buffer("camera");
    Eigen::MatrixXd somemat;
    somemat.resize(4,4);somemat.setIdentity();
    somemat<<1,0,0,0,
        0,0,1,0,
        0,-1,0,0,
        0,0,0,1;
    m_animator->Add_Camera(somemat,0.25,"camera");
//总是要画一个基准点的，算了吧，这个以后再说
    m_animator->GLEnableVertexAttribArray(0);
    m_animator->GLVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, nullptr);

    //接下来就是比较头疼的事情了，如何写buffer能够迭代式的压入新点
    //嘛，下一步再说，先出去走走
    //先绘制摄像机吧
    //我们不希望每次都需要从底层逻辑绘制3D图像，所以
    //应该使用一些高级功能绘制物体
    //iterate看起来不行，必须清空从头来，在这里搞定iterate的工作？
    //可能会严重拖慢性能哦...

    //没有办法，目前看到的所有信息都告诉我们，必须摧毁原有的buffer然后重新压入
    //当然，这个过程可以让animator3D自行解决
    //m-animator.create_Buffer(vbo)
    //m-animator.pushdata(vbo,std::vector<float> some_data)

    //    GLfloat additionalData[] = {    -2.2f, 2.0f, 2.0f,
    //        1.4f, 1.6f, 1.0f,
    //        -1.2f, 1.0f, 1.4f,};
    //    GLintptr offset = sizeof(cubebuffer);
    //    GLsizeiptr additionalDataSize = sizeof(additionalData);
    //    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vbo);
    //    m_animator->GLBufferSubData(GL_ARRAY_BUFFER, offset-current_buffer_size, additionalDataSize, additionalData);
    //    m_animator->GLEnableVertexAttribArray(0);
    //    m_animator->GLVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, nullptr);
    //    counter++;
}

void Slam_Drawer::addoneslot()
{
//    std::vector<float> data = {0,0,0+(float)counter,
//                               1,0,0+(float)counter,
//                               0.5,1,0+(float)counter};

//    m_animator->Push_Data2buffer("testcubic",data);
//    Eigen::MatrixXd somemat;
//    somemat.resize(4,4);somemat.setIdentity();
//    somemat(0,3)=counter;somemat(1,3)=counter;somemat(2,3)=counter;
//    m_animator->Add_Camera(somemat,"camera");
////不对，像是数据被漏掉了，我们要求检查
//    //没漏掉，第一次插入的数据和之前的数据一模一样...
    //    counter++;
}

void Slam_Drawer::add_pos(Eigen::MatrixXd Trans)
{
    m_animator->Add_Camera(Trans,0.25,"camera");
}
