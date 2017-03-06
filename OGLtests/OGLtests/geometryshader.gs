#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 texCoords;
	vec3 Normal;
	vec3 Position;
} gs_in[];

out GS_OUT {
    vec2 texCoords;
	vec3 Normal;
	vec3 Position;
} gs_out;




void main() {    
    

    gl_Position = gl_in[0].gl_Position;
	gs_out.texCoords = gs_in[0].texCoords;
	gs_out.Normal = gs_in[0].Normal;
	gs_out.Position = gs_in[0].Position;
    EmitVertex();
	gl_Position = gl_in[1].gl_Position;
    gs_out.texCoords = gs_in[1].texCoords;
	gs_out.Normal = gs_in[1].Normal;
	gs_out.Position = gs_in[1].Position;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
    gs_out.texCoords = gs_in[2].texCoords;
	gs_out.Normal = gs_in[2].Normal;
	gs_out.Position = gs_in[2].Position;
    EmitVertex();
    EndPrimitive();
}