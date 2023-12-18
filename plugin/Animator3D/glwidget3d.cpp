#include "glwidget3d.h"
#include <cmath>
glwidget3D::glwidget3D(QWidget *parent)
{
    setMouseTracking(true);
    elapsed = 0;
    m_width=1000;//默认大小
    m_height=600;
    //    setFixedSize(m_width, m_height);
    setAutoFillBackground(false);
    nearplanedis=0.1;
    farplanedis=1000;
    FOV=45;

    position = glm::vec3(0, 0, 0);
    horizontalAngle = 3.14f;
    // vertical angle : 0, look at the horizon
    verticalAngle = 0.0f;
    // Initial Field of View
    speed = 3.0f; // 3 units / second
    mousespeed = 0.0005f;
    rotateCams(0,0);
    ProjectionMatrix = glm::perspective(glm::radians(FOV), float(m_width)/ float(m_height), nearplanedis, farplanedis);
    //    initializeGL();
    Channel_R=0;
    Channel_G=0;
    Channel_B=0;
    Channel_A=1;

    glm::vec3 axisz(0.0f, 0.0f, 1.0f); // 绕Z轴旋转
    glm::mat4 rotationMatrix= glm::mat4(1.0f);
    camera_frame_T=glm::rotate(rotationMatrix, float(M_PI), axisz);//旋转180度
    glm::vec3 axisy(0.0f, 1.0f, 0.0f); // 绕Y轴旋转
    camera_frame_T=glm::rotate(camera_frame_T, float(M_PI), axisy);//旋转180度
    //这是摄像机坐标系
    //通过上面两步实现了ZED摄像机点云到正常能看的坐标的转化，现在的坐标系为，原点在屏幕中央，右x下y前z


    Transformworld2worldMat=camera_frame_T;
    //默认使用的摄像机坐标系
    glm::vec3 axisx(1.0f, 0.0f, 0.0f); // 绕X轴旋转
    world_frame_T=glm::rotate(rotationMatrix, float(M_PI), axisz);//旋转180度
    world_frame_T=glm::rotate(world_frame_T, float(M_PI), axisy);//旋转180度
    world_frame_T=glm::rotate(world_frame_T, float(M_PI)/2, axisx);//旋转90度
}

void glwidget3D::GLBufferSubData(unsigned int target, ptrdiff_t offset, ptrdiff_t size, const void *data)
{
    glBufferSubData(target,offset,size,data);
}

void glwidget3D::SetModelmat(glm::mat4 &Model)
{
    glUseProgram(m_programID);
    GLuint MatrixID = glGetUniformLocation(m_programID, "Modelmat");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Model[0][0]);
}

void glwidget3D::set_glpainter(glpainter3D *m_paint)
{
    m_painter=m_paint;
}

unsigned int glwidget3D::GLGetUniformLocation(unsigned int programID, const char *name)
{
    return glGetUniformLocation(programID, name);
}

void glwidget3D::GLUniformMatrix4fv(int MatrixID, int count, unsigned char transpose, const float *value)
{
    glUniformMatrix4fv(MatrixID, count, transpose, value);
}

void glwidget3D::GLUseProgram(unsigned int programID)
{
    glUseProgram(programID);
}

void glwidget3D::GLVertexAttribPointer(unsigned int indx, int size, unsigned int type, unsigned char normalized, int stride, const void *ptr)
{
    glVertexAttribPointer(indx,size, type, normalized,stride, ptr);
}

void glwidget3D::GLEnableVertexAttribArray(int index)
{
    glEnableVertexAttribArray(index);
}

void glwidget3D::GLBindBuffer(unsigned int target, unsigned int buffer)
{
    glBindBuffer(target, buffer);
}

void glwidget3D::GLBufferData(unsigned int target, ptrdiff_t size, const void *data, unsigned int usage)
{
    glBufferData(target,size, data, usage);
}

void glwidget3D::GLGenBuffers(int num, unsigned int *buf)
{
    glGenBuffers(num, buf);
}

void glwidget3D::GLDrawArrays(unsigned int glmode,  int start,  int length)
{
    glDrawArrays(glmode, start, length);
}

void glwidget3D::rotateCams(int x, int y)
{
    horizontalAngle += mousespeed * float(x);
    verticalAngle += mousespeed * float(y);

    //本来就是deltax了，不需要再加2/1量
    direction=glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
        );

    // Right vector
    right = glm::vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
        );
    // Up vector
    up = glm::cross(right, direction);
    ViewMatrix = glm::lookAt(
        position,           // Camera is here
        position + direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
        );

}

void glwidget3D::move_in_direction(glm::vec3 direc)
{
    float deltaTime=0.01;
    position += direc * deltaTime * speed;
    ViewMatrix = glm::lookAt(
        position,           // Camera is here
        position + direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
        );
}

void glwidget3D::resizeGLwidget(int w, int h)
{
    resize(w,h);
    m_width=w;
    m_height=h;
    //默认视场角度为45不可更改
    ProjectionMatrix = glm::perspective(glm::radians(FOV), float(m_width)/ float(m_height), nearplanedis, farplanedis);
}

void glwidget3D::mouseMoveEvent(QMouseEvent *event)
{
    m_painter->get_mouse_pos(event->x(),event->y());
}

GLuint glwidget3D::LoadShaders(const char *vertex_file_path, const char *fragment_file_path)
{
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}


void glwidget3D::animate()
{
    update();
}


void glwidget3D::initializeGL()
{
    initializeOpenGLFunctions();


    // 生成VAO，如果不加是不是也行呢....
    //因为就算在教程中，VAO好像也没有用
    vao = new QOpenGLVertexArrayObject;
    bool iscreta=vao->create();
    vao->bind();

    //这两句话等效于下面的这两句？
    //    glGenVertexArrays(1, &m_vao);
    //    glBindVertexArray(m_vao);
    //以后很有可能出现需要改shader的情况
    //所以最好的方式是，将所有的基础接口都公共化，然后提供一些复合接口
    //        m_programID = LoadShaders("vertexview.shader", "Fragcolorset.shader");
    // 不行，这些步骤只能在initialize里面部署......
    //我们能够做的就是运行时修改buffer里面的数据
    //换言之，下面这些函数全部不是我们这一层能用的
    //    GLuint vertexbuffer;
    //    glGenBuffers(1, &vertexbuffer);
    //    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    //    // 将vertex数据塞进来
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(cubebuffer), cubebuffer, GL_STATIC_DRAW);
    m_painter->initialization();
    //    GLuint vertexcolorbuffer;
    //    glGenBuffers(1, &vertexcolorbuffer);
    //    glBindBuffer(GL_ARRAY_BUFFER, vertexcolorbuffer);
    //    // 将vertex颜色数据塞进来
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    // Create a shader program

    // Set the clear color to black
    glClearColor(Channel_R, Channel_G,Channel_B, Channel_A);

    // Specify the layout of the vertex data
    //    glEnableVertexAttribArray(0);
    //    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, nullptr);
    //    glEnableVertexAttribArray(1);
    //    glBindBuffer(GL_ARRAY_BUFFER, vertexcolorbuffer);
    //    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0, nullptr);
    // Enable depth test
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
//绘制点的尺寸，在shader里面更改
    //点尺寸的设定在shader里面
    //有一些无法在这里进行的设定都在shader里面执行
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glUseProgram(m_programID);
    glm::mat4 Model = glm::mat4(1.0f);
    GLuint MatrixID = glGetUniformLocation(m_programID, "Modelmat");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Model[0][0]);
}

void glwidget3D::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    m_width=w;
    m_height=h;

}

void glwidget3D::paintGL()
{
    //有点麻烦，假设在这里调用glpainter3d paint，就对不上openGL的逻辑
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Use the shader program
    //        glUseProgram(m_programID);


    //    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 ViewProjmat = ProjectionMatrix * ViewMatrix*Transformworld2worldMat; // Remember, matrix multiplication is the other way around
    //如果想要使用视角矩阵，那么公用programID就是必然的
    //不然的话，就必须要求每个program单独输入视角矩阵
    //后者的灵活度更高，前者的封装更好
    //考虑到我们本来就很少使用多个shader，我想应该OK？
    //但是不要删除这里的comment，以便于以后需要的时候做更改
    GLuint MatrixID = glGetUniformLocation(m_programID, "ViewProjmat");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &ViewProjmat[0][0]);
    // Draw the triangle
    //            glDrawArrays(GL_TRIANGLES, 0, 36);
    m_painter->paint();
        //呃，有点儿奇怪...
        //好像是窗口本身的压缩问题
        //看起来的视角有一点儿....不正？
}
