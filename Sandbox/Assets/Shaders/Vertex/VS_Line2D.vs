#version 430 core
layout (location = 0) in vec2 aPos;

uniform mat3 projection;

void main()
{
	vec3 test = vec3(aPos.x, aPos.y, 1.0);
	test = projection * test;
	gl_Position=vec4(test.x, test.y, 0.0, 1.0);
}