#include "cubedrawer.h"

cubedrawer::cubedrawer()
{

}

void cubedrawer::draw()
{
  // m_animator->GLDrawArrays(GL_TRIANGLES, 0, 36);//gl指令无法穿透，必须借助animator的穿透了
    //还有一个注册的问题



    m_animator->GLDrawArrays(GL_TRIANGLES, 0, 36);
    //点尺寸的设定在shader里面


    //基本的设计思路，将gl的指令借助service和glpainter穿透到glwidget里面
}

void cubedrawer::initialization()
{
    //下面这两行创建shader程序，只在第一个注册的程序中写就可以了
    programID = m_animator->LoadShaders("vertexview.shader", "Fragcolorset.shader");
    m_animator->SetPainterID(programID);
    // 不行，这些步骤只能在initialize里面部署......
    //我们能够做的就是运行时修改buffer里面的数据
    //换言之，下面这些函数全部不是我们这一层能用的
    GLuint vertexbuffer;
    m_animator->GLGenBuffers(1, &vertexbuffer);
    m_animator->GLBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    m_animator->GLBufferData(GL_ARRAY_BUFFER, sizeof(cubebuffer), cubebuffer, GL_STATIC_DRAW);

    GLuint vertexcolorbuffer;
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
        //这些初始化函数必须在initialization里面唤起

    glm::mat4 Model = glm::mat4(1.0f);
    GLuint MatrixID = m_animator->GLGetUniformLocation(programID, "Modelmat");
    m_animator->GLUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Model[0][0]);
    //默认不运动的矩阵
}
