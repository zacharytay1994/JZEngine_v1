#version 450 core

out vec4 FragColor;
in vec3 vPos;

void main () 
{
	FragColor=vec4(vPos, 1.0);
}