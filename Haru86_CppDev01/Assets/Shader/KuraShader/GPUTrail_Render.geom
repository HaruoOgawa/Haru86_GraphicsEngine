#version 430

layout(points) in;
layout(points,max_vertices=1) out;

in float v2g_flag[];

out float g2f_flag;

uniform float _time;

void main(){
	gl_Position=gl_in[0].gl_Position;
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	EndPrimitive();
}
