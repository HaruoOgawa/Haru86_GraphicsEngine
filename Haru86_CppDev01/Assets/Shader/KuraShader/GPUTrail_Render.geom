#version 430

layout(points) in;
layout(triangle_strip,max_vertices=6) out;

in float v2g_flag[];
in vec3 v2g_pos[];

out float g2f_flag;

uniform mat4 MVPMatrix;
uniform mat4 MMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform float _time;

#define PI 3.14159265
#define rot(a) mat2(cos(a),sin(a),-sin(a),cos(a))

float rand(vec2 seeds){
  return fract(sin(dot(seeds, vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
	vec3 pos=v2g_pos[0];
	float size=1.0+sin(_time)*0.5;
	//prim 1//////////////////////////////////////////////////////
	vec3 outPos=gl_in[0].gl_Position.xyz+vec3(1.0,1.0,0.0)*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos+v2g_pos[0],1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	outPos=gl_in[0].gl_Position.xyz+vec3(-1.0,1.0,0.0)*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos+v2g_pos[0],1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	outPos=gl_in[0].gl_Position.xyz+vec3(-1.0,-1.0,0.0)*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos+v2g_pos[0],1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	EndPrimitive();
	
	//prim 2//////////////////////////////////////////////////////
	outPos=gl_in[0].gl_Position.xyz+vec3(-1.0,-1.0,0.0)*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos+v2g_pos[0],1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	outPos=gl_in[0].gl_Position.xyz+vec3(1.0,-1.0,0.0)*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos+v2g_pos[0],1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	outPos=gl_in[0].gl_Position.xyz+vec3(1.0,1.0,0.0)*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos+v2g_pos[0],1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	EndPrimitive();
}
