#version 430 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in mat3 transform;

out vec2 TexCoord;

void main()
{
	vec3 test = vec3(aPos.x, aPos.y, 1.0);
	test = transform * test;
	gl_Position=vec4(test.x, test.y, 0.0, 1.0);

	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}