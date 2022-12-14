#version 450 core
layout (location = 0) in vec3 i_vertex;

void main()
{
    gl_Position = vec4(i_vertex, 1);
}