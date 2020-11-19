#version 330 core
layout (location = 0) in vec2 vertex_position;
layout (location = 1) in vec2 vertex_uv;
out vec2 fragment_position;
//out vec2 fragment_uv;
uniform mat4 camera_matrix;
void main()
{
  // camera_matrix * 
  gl_Position.xy = (vec4(vertex_position, 0.0f, 1.0f)).xy;
  gl_Position.z = 0.0f;
  gl_Position.w = 1.0f;
  fragment_position = vertex_position.xy;
  //fragment_uv = vertex_uv;
}