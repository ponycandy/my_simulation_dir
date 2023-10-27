#include "glwidget3d.h"

glwidget3D::glwidget3D(QWidget *parent)
{
    setMouseTracking(true);
    elapsed = 0;
    m_width=1000;//默认大小
    m_height=600;
    //    setFixedSize(m_width, m_height);
    setAutoFillBackground(false);

}

void glwidget3D::set_glpainter(glpainter3D *m_paint)
{
    m_painter=m_paint;
}

void glwidget3D::resizeGLwidget(int w, int h)
{
    resize(w,h);
    m_width=w;
    m_height=h;
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint vertexcolorbuffer;
    glGenBuffers(1, &vertexcolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexcolorbuffer);
    // 将vertex颜色数据塞进来
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    // Create a shader program
    programID = LoadShaders("vertex.shader", "Frag.shader");


    // Specify the layout of the vertex data
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexcolorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0, nullptr);

}

void glwidget3D::resizeGL(int, int)
{
    // m_projection.setToIdentity();
    //   m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);

}

void glwidget3D::paintGL()
{

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the shader program
    glUseProgram(programID);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

}
