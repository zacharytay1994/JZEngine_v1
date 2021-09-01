#version 450 core

layout (location=0) in vec3 vInterpColor;
layout (location=0) out vec4 fFragColor;

void main () 
{
	fFragColor=vec4(vInterpColor, 1.0);
}