#version 330 core

uniform vec4 u_color;

out vec4 gl_FragColor;

void main()
{
    gl_FragColor = u_color;
}
