#version 450 core

layout (location=8) in vec2 aVertexPosition;
layout (location=9) in vec3 aVertexColor;
layout (location=0) out vec3 vColor;

void main() 
{
	gl_Position=vec4(aVertexPosition, 0.0, 1.0);
	vColor=aVertexColor;
}