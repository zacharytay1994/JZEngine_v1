#version 430 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D scene;
uniform vec2 offsets[9];
uniform int	edge_kernel[9];
uniform float blur_kernel[9];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

void main()
{
    // zero out memory since an out variable is initialized with undefined values by default 
    color = vec4(0.0f);
    
    vec3 temp_data[9];

    // sample from texture offsets if using convolution matrix
    if(chaos || shake)
    {
        for(int i = 0; i < 9; i++)
        {
            temp_data[i] = vec3(texture(scene, TexCoords.st + offsets[i]));
        }
    }

    // process effects
    if(chaos)
    {           
        for(int i = 0; i < 9; i++)
            color += vec4(temp_data[i] * edge_kernel[i], 0.0f);
        color.a = 1.0f;
    }
    else if(confuse)
    {
        color = vec4(1.0 - texture(scene, TexCoords).rgb, 1.0);
    }
    else if(shake)
    {
        for(int i = 0; i < 9; i++)
            color += vec4(temp_data[i] * blur_kernel[i], 0.0f);
        color.a = 1.0f;
    }
    else
    {
        color =  texture(scene, TexCoords);
    }
}