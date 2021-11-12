#version 430 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform vec3 tint;
uniform float time;

void main()
{
	vec4 outCol = texture(texture1, vec2(TexCoord.x + sin(((TexCoord.y*6.0f)+(time*0.05f))*3.14f)*0.006f, TexCoord.y));
	outCol = vec4 (outCol.x+((1-outCol.x)*tint.x), outCol.y+((1-outCol.y)*tint.y),outCol.z+((1-outCol.z)*tint.z), outCol.w); 
	FragColor = outCol;
}