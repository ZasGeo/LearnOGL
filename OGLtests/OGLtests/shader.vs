// Vertex shader:
// ================
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;



out VS_OUT {
    vec2 texCoords;
	vec3 Normal;
	vec3 Position;
} vs_out;

uniform mat4 model;

layout (std140) uniform Matrices
{
      mat4 view;
      mat4 projection;
}; 


void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    vs_out.Normal = mat3(transpose(inverse(model))) * normal;
    vs_out.Position = vec3(model * vec4(position, 1.0f));
	vs_out.texCoords = texCoords;
}