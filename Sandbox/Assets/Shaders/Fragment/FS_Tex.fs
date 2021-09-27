#version 430 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform vec3 tint;

void main()
{
	vec4 outCol = texture(texture1, TexCoord);
	outCol = vec4 (outCol.x+((1-outCol.x)*tint.x), outCol.y+((1-outCol.y)*tint.y) ,outCol.z+((1-outCol.z)*tint.z), outCol.w); 
	FragColor = outCol;
}