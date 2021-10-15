#version 430 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform vec4 tint;

void main()
{
	vec4 outCol = texture(texture1, TexCoord);
	float blackwhite = ((outCol.x*tint.x) + (outCol.y*tint.y) + (outCol.z*tint.z)) / 3.0;
	FragColor = vec4(blackwhite, blackwhite, blackwhite, outCol.w*tint.w);
}