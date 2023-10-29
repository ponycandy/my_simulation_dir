#include "glwidget3d.h"

glwidget3D::glwidget3D(QWidget *parent)
{
    setMouseTracking(true);
    elapsed = 0;
    m_width=1000;//默认大小
    m_height=600;
    //    setFixedSize(m_width, m_height);
    setAutoFillBackground(false);
    nearplanedis=0.1;
    farplanedis=100;
    FOV=45;

    position = glm::vec3(0, 0, 5);
    horizontalAngle = 3.14f;
    // vertical angle : 0, look at the horizon
    verticalAngle = 0.0f;
    // Initial Field of View
    speed = 3.0f; // 3 units / second
    mousespeed = 0.00005f;
    rotateCams(0,0);
    ProjectionMatrix = glm::perspective(glm::radians(FOV), float(m_width)/ float(m_height), nearplanedis, farplanedis);

}

void glwidget3D::set_glpainter(glpainter3D *m_paint)
{
    m_painter=m_paint;
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

    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // 生成VAO，如果不加是不是也行呢....
    //因为就算在教程中，VAO好像也没有用
    vao = new QOpenGLVertexArrayObject;
    bool iscreta=vao->create();
    vao->bind();
    //这两句话等效于下面的这两句？
    //    glGenVertexArrays(1, &m_vao);
    //    glBindVertexArray(m_vao);

    // 下面这一步和opengl里面是一样的，绑定数据容器
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // 将vertex数据塞进来
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubebuffer), cubebuffer, GL_STATIC_DRAW);

    GLuint vertexcolorbuffer;
    glGenBuffers(1, &vertexcolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexcolorbuffer);
    // 将vertex颜色数据塞进来
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    // Create a shader program
    programID = LoadShaders("vertexview.shader", "Fragcolorset.shader");


    // Specify the layout of the vertex data
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexcolorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0, nullptr);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
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
    glUseProgram(programID);
    m_painter->paint();

    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * Model; // Remember, matrix multiplication is the other way around

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //呃，有点儿奇怪...
    //好像是窗口本身的压缩问题
    //看起来的视角有一点儿....不正？
}
