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

void glpainter3D::SetModelmat(glm::mat4 &Model)
{
    m_glwidget->SetModelmat(Model);
}

void glpainter3D::GLBufferSubData(unsigned int target, ptrdiff_t offset, ptrdiff_t size, const void *data)
{
    m_glwidget->GLBufferSubData(target,offset,size,data);
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

void glpainter3D::GLBindBuffer(unsigned int target, unsigned int buffer)
{
    m_glwidget->GLBindBuffer(target,buffer);
}

void glpainter3D::drawcube(float Dx, float Dy, float Dz, float centerx, float centery, float centerz, float alpha, float beta, float gama)
{

}

void glpainter3D::resizeWindow(int width, int height)
{

}

void glpainter3D::GLDrawArrays(unsigned int glmode, int start, int length)
{
    m_glwidget->GLDrawArrays(glmode,start,length);
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
