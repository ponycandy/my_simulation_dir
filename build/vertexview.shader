#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
uniform mat4 ViewProjmat; 
uniform mat4 Modelmat;
out vec3 fragmentColor;


void main()
{
  
  gl_Position = ViewProjmat* Modelmat* vec4(vertexPosition_modelspace,1);
  fragmentColor = vertexColor;
gl_PointSize = 10;

}
