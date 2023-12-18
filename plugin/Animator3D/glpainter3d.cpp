#include "glpainter3d.h"

glpainter3D::glpainter3D(QObject *parent)
{
    QSurfaceFormat format;
    format.setVersion(4, 3);    // 关键是这一句，设置opengl版本号
    QSurfaceFormat::setDefaultFormat(format);

    m_widget=new base_widget;
    m_glwidget=new glwidget3D(m_widget);
    m_glwidget->set_glpainter(this);
    m_widget->setpainter(this);

    m_width=1000;
    m_height=600;
    background.setColor(Qt::black);
    background.setStyle(Qt::SolidPattern);

    factorin=1;
    pixel_per_meter=30;//initial condition
    calc_bounder();
    mousex=0;recorded_mouse_x=0;operation_num=0;
    mousey=0;recorded_mouse_y=0;mouse_is_pressed=0;
    //    resizeWindow(400,300);
    setupUI();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, m_glwidget, &glwidget3D::animate);


}

void glpainter3D::setupUI()
{
    layout = new QGridLayout;
    layout->addWidget(m_glwidget);
    //    layout->setContentsMargins();
    m_widget->setLayout(layout);
    //    m_widget->show();
    //    m_widget->resize(m_width,m_height);
}

void glpainter3D::Draw_Camera(std::string buffer_name)
{
    std::shared_ptr<std::vector<float>> data_stored=name_2_datamap.value(buffer_name);
    GLuint vbo=name_2_buffermap.value(buffer_name);
    m_glwidget->GLBindBuffer(GL_ARRAY_BUFFER, vbo);
    m_glwidget->GLDrawArrays(GL_LINES, 0, data_stored->size() * sizeof(float));
}

void glpainter3D::Set_Frame_world()
{
    m_glwidget->Transformworld2worldMat=m_glwidget->world_frame_T;
}

void glpainter3D::Set_Frame_Camera()
{
    m_glwidget->Transformworld2worldMat=m_glwidget->camera_frame_T;
}

void glpainter3D::Add_Camera(Eigen::MatrixXd &Trans, std::string buffer_name)
{
    GLuint vbo=name_2_buffermap.value(buffer_name);
    std::shared_ptr<std::vector<float>> data_stored=name_2_datamap.value(buffer_name);
    //接下来根据Trans生成8个顶点
    float scale=1;
    std::vector<Eigen::MatrixXd> points;
    //下面首先完成线框
    Eigen::MatrixXd R_B;R_B.resize(4,1);R_B<<0.5*scale,0,0.5*scale,1;
    Eigen::MatrixXd R_F;R_F.resize(4,1);R_F<<0.5*scale,0,-0.5*scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<0.5*scale,0,-0.5*scale,1;R_F<<-0.5*scale,0,-0.5*scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<-0.5*scale,0,-0.5*scale,1;R_F<<-0.5*scale,0,0.5*scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<-0.5*scale,0,0.5*scale,1;R_F<<0.5*scale,0,0.5*scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<0.5*scale,0,0.5*scale,1;R_F<<scale,scale,scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<scale,scale,scale,1;R_F<<-scale,scale,scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<-scale,scale,scale,1;R_F<<-scale,scale,-scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<-scale,scale,-scale,1;R_F<<scale,scale,-scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<scale,scale,-scale,1;R_F<<scale,scale,scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<-scale,scale,scale,1;R_F<<-0.5*scale,0,0.5*scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<-scale,scale,-scale,1;R_F<<-0.5*scale,0,-0.5*scale,1;
    points.push_back(R_B);points.push_back(R_F);

    R_B<<scale,scale,-scale,1;R_F<<0.5*scale,0,-0.5*scale,1;
    points.push_back(R_B);points.push_back(R_F);
    //然后作transformation
    for(auto point:points)
    {
        Eigen::MatrixXd cam_P=Trans*point;
        std::vector<float> data;//xyz坐标压入到buffer里面
        data.push_back(cam_P(0,0));data.push_back(cam_P(1,0));data.push_back(cam_P(2,0));
        Push_Data2buffer(buffer_name,data);
    }
}

void glpainter3D::Create_Buffer(std::string buffer_name)
{
    GLuint buf;
    m_glwidget->GLGenBuffers(1,&buf);
    name_2_buffermap.insert(buffer_name,buf);
    std::shared_ptr<std::vector<float>> ptr(new std::vector<float>);
    name_2_datamap.insert(buffer_name,ptr);

}

void glpainter3D::Draw_Triangular(std::string buffername)
{
    std::shared_ptr<std::vector<float>> data_stored=name_2_datamap.value(buffername);
    GLuint vbo=name_2_buffermap.value(buffername);
    m_glwidget->GLBindBuffer(GL_ARRAY_BUFFER, vbo);
    m_glwidget->GLDrawArrays(GL_TRIANGLES, 0, data_stored->size() * sizeof(float));
}

void glpainter3D::Push_Data2buffer(std::string buffer_name, std::vector<float> data)
{
    //这个功能的bug，不知道为什么第一下没有用....
    GLuint vbo=name_2_buffermap.value(buffer_name);
    std::shared_ptr<std::vector<float>> data_stored=name_2_datamap.value(buffer_name);
    data_stored->insert(data_stored->end(), data.begin(), data.end());

    m_glwidget->GLBindBuffer(GL_ARRAY_BUFFER, vbo);
    m_glwidget->GLBufferData(GL_ARRAY_BUFFER, data_stored->size() * sizeof(float),
                             data_stored->data(), GL_DYNAMIC_DRAW);
}

void glpainter3D::setbackgroundColor(float R, float G, float B, float A)
{
    m_glwidget->Channel_A=A;
    m_glwidget->Channel_R=R;
    m_glwidget->Channel_G=G;
    m_glwidget->Channel_B=B;
}


void glpainter3D::SetModelmat(glm::mat4 &Model)
{
    m_glwidget->SetModelmat(Model);
}

void glpainter3D::GLBufferSubData(unsigned int target, ptrdiff_t offset, ptrdiff_t size, const void *data)
{
    m_glwidget->GLBufferSubData(target,offset,size,data);
    //只能够修改已有的数据，无法添加新的数据
}

void glpainter3D::SetPainterID(unsigned int programID)
{
    m_glwidget->m_programID=programID;
}

void glpainter3D::get_mouse_pos(int x, int y)
{
    if(mouse_is_pressed==0)
    {
        //xy是从左上角为原点的坐标系下的坐标
        mousex=x;
        mousey=y;
        //什么都不做
    }
    else
    {
        //这里执行旋转摄像头的操作
        int delta_x=x-mousex;//偏离原点的量
        int delta_y=y-mousey;//偏离原点的量
        //这里没问题，那就只能是旋转有问题了
        rotateCams(-delta_x, -delta_y);
        //        qDebug()<<"delta_x is "<<delta_x;
        //        qDebug()<<"mousex is "<<mousex;
        //        qDebug()<<"x is "<<x;
        //        qDebug()<<"delta_y is "<<delta_y;
        //        qDebug()<<"mousey is "<<mousey;
        //        qDebug()<<"y is "<<y;
        //我们要仔细思考三维场景下的变换公式
        //我们的鼠标移动的始终是视角
        mousex=x;
        mousey=y;
    }
}

void glpainter3D::GLUniformMatrix4fv(int MatrixID, int count, unsigned char transpose, const float *value)
{
    m_glwidget->GLUniformMatrix4fv(MatrixID,count,transpose,value);
}

void glpainter3D::GLUseProgram(unsigned int programID)
{
    m_glwidget->GLUseProgram(programID);
}

unsigned int glpainter3D::GLGetUniformLocation(unsigned int programID, const char *name)
{
    return m_glwidget->GLGetUniformLocation(programID,name);
}

void glpainter3D::GLVertexAttribPointer(unsigned int indx, int size, unsigned int type, unsigned char normalized, int stride, const void *ptr)
{
    m_glwidget->GLVertexAttribPointer(indx,size,type,normalized,stride,ptr);
}

void glpainter3D::GLBufferData(unsigned int target, ptrdiff_t size, const void *data, unsigned int usage)
{
    m_glwidget->GLBufferData(target,size,data,usage);
}

void glpainter3D::GLGenBuffers(int num, unsigned int *buf)
{
    m_glwidget->GLGenBuffers(num,buf);
}

void glpainter3D::setCameraPOS(float x, float y, float z)
{
    m_glwidget->position = glm::vec3(x, y, z);
}

void glpainter3D::GLBindBuffer(unsigned int target, unsigned int buffer)
{
    m_glwidget->GLBindBuffer(target,buffer);
}

void glpainter3D::drawcube(float Dx, float Dy, float Dz, float centerx, float centery, float centerz, float alpha, float beta, float gama)
{

}

void glpainter3D::drawcamera(float Dx, float Dy, float Dz, float centerx, float centery, float centerz, float alpha, float beta, float gama)
{

}

void glpainter3D::drawcamera_Iterate(float Dx, float Dy, float Dz, float centerx, float centery, float centerz, float alpha, float beta, float gama)
{

}

void glpainter3D::resizeWindow(int width, int height)
{

}

void glpainter3D::GLDrawArrays(unsigned int glmode, int start, int length)
{
    m_glwidget->GLDrawArrays(glmode,start,length);
}

void glpainter3D::setCameraParms(float nearP, float farP, float LinearSpeed, float RotSpeed)
{
    m_glwidget->nearplanedis=nearP;
    m_glwidget->farplanedis=farP;
    m_glwidget->speed=LinearSpeed;
    m_glwidget->mousespeed=RotSpeed;
    m_glwidget->ProjectionMatrix = glm::perspective(
        glm::radians(m_glwidget->FOV),
        float(m_glwidget->m_width)/ float(m_height),
        m_glwidget->nearplanedis, m_glwidget->farplanedis);

}

void glpainter3D::start_animate()
{
    timer->start(10);
}

void glpainter3D::stop_animate()
{
    timer->stop();
}

unsigned int glpainter3D::LoadShaders(const char *vertex_file_path, const char *fragment_file_path)
{
    unsigned int  ID=m_glwidget->LoadShaders(vertex_file_path,fragment_file_path);
    return ID;
}

void glpainter3D::register_painter(Drawer3D *painter)
{
    operation_num+=1;
    DrawOperation_map.insert(operation_num,painter);
    painter->m_animator=this;
    //在这里同时完成Drawer3D的初始化内容
}

void glpainter3D::GLEnableVertexAttribArray(int index)
{
    m_glwidget->GLEnableVertexAttribArray(index);
}

Animateservice3Dservice *glpainter3D::cloneservice()
{
    glpainter3D *servicenew=new glpainter3D;
    return servicenew;
}

QWidget *glpainter3D::getwidget()
{
    return m_widget;
}

void glpainter3D::paint()
{
    for(int i=1;i<=operation_num;i++)
    {
        DrawOperation_map.value(i)->draw();
    }


}

void glpainter3D::initialization()
{
    for(int i=1;i<=operation_num;i++)
    {
        DrawOperation_map.value(i)->initialization();
    }
}

void glpainter3D::zoomin()
{

}

void glpainter3D::zoomout()
{

}

void glpainter3D::calc_bounder()
{

}

void glpainter3D::moveup()
{
    m_glwidget->move_in_direction(m_glwidget->up);
}

void glpainter3D::movedown()
{
    m_glwidget->move_in_direction(-m_glwidget->up);

}

void glpainter3D::moveright()
{
    m_glwidget->move_in_direction(m_glwidget->right);
}

void glpainter3D::moveleft()
{
    m_glwidget->move_in_direction(-m_glwidget->right);
}

void glpainter3D::movein()
{
    m_glwidget->move_in_direction(m_glwidget->direction);
}

void glpainter3D::moveout()
{
    m_glwidget->move_in_direction(-m_glwidget->direction);

}

void glpainter3D::rotateCams(int x, int y)
{
    m_glwidget->rotateCams( x,  y);
}

void glpainter3D::record_pressed_mouse(int x, int y)
{
    //    mousex=x;
    //    mousey=y;
}
