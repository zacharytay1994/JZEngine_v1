#version 430 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform float myAlpha;

void main()
{
    vec4 outCol = texture(ourTexture, TexCoord);
    FragColor = vec4 (outCol.x , outCol.y , outCol.z , outCol.w*myAlpha);
}