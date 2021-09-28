#version 430 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec4 outCol = texture(texture1, TexCoord);
	outCol.x = 1.0;
	FragColor = outCol;
}