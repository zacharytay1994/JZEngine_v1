#version 430 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 transform;

void main()
{
    gl_Position = vec4(aPos + transform, 0.0, 1.0);
}