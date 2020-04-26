#version 330 core
layout (location = 0) in vec3 a_position;

uniform mat4 u_projModelView;

void main()
{
    gl_Position = u_projModelView * vec4(a_position, 1.0f);
}
