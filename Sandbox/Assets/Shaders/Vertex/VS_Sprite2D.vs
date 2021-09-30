#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat3 transform;

void main()
{
	//gl_Position = vec4(aPos.x+1,aPos.yz, 1.0);
	vec3 test = vec3(aPos.x, aPos.y, 1.0);
	test = transform * test;
	gl_Position=vec4(test.x, test.y, 0.0, 1.0);

	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}