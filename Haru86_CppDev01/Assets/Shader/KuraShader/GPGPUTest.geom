#version 430

layout(triangles) in;
layout(triangle_strip,max_vertices=3) out;

in vec2 uv[];
in vec4 velocity[];
in vec3 randCol[];
in vec3 v2g_normal[];

out vec2 g2f_uv;
out vec4 g2f_velocity;
out vec3 g2f_randCol;

uniform float _time;

void main(){
	gl_Position=gl_in[0].gl_Position;
	g2f_uv=uv[0];
	g2f_velocity=velocity[0];
	g2f_randCol=randCol[0];
	EmitVertex();
	
	gl_Position=gl_in[1].gl_Position;
	g2f_uv=uv[1];
	g2f_velocity=velocity[1];
	g2f_randCol=randCol[1];
	EmitVertex();
	
	gl_Position=gl_in[2].gl_Position;
	g2f_uv=uv[2];
	g2f_velocity=velocity[2];
	g2f_randCol=randCol[2];
	EmitVertex();

	EndPrimitive();
}
