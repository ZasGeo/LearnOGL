#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;

void main()
{    
    color = vec4(texture(texture_normal1, TexCoords));
}