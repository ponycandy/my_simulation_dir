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

void glwidget3D::Loadshader()
{
    QOpenGLShaderProgram program;
    program.addShaderFromSourceCode(QOpenGLShader::Vertex, "vertex.shader");
    program.addShaderFromSourceCode(QOpenGLShader::Fragment, "Frag.shader");
    program.link();
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
    vao->bind();//这两句话等效于下面的这两句？
//    glGenVertexArrays(1, &m_vao);
//    glBindVertexArray(m_vao);

    // Create a vertex buffer object
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Define the vertex data for the triangle
    GLfloat vertices[] = {
        // Positions        // Colors
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Bottom left
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom right
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Top
    };

    // Upload the vertex data to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create a shader program
    m_program = glCreateProgram();

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos; // Position attribute
        layout (location = 1) in vec3 aColor; // Color attribute

        out vec3 vColor; // Output color to the fragment shader

        void main()
        {
            gl_Position = vec4(aPos, 1.0); // Set the position
            vColor = aColor; // Pass the color to the next stage
        }
    )";
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec3 vColor; // Input color from the vertex shader

        out vec4 FragColor; // Output color to the screen

        void main()
        {
            FragColor = vec4(vColor, 1.0); // Set the color
        }
    )";
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Attach and link the shaders to the program
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    // Delete the shaders as they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(m_program, "aPos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(GLfloat), nullptr);

    GLint colAttrib = glGetAttribLocation(m_program, "aColor");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

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
    glUseProgram(m_program);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

}
