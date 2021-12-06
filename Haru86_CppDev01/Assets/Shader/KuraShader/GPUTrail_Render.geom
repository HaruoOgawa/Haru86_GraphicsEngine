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
	float size=2000.0;
	//prim 1
	vec3 outPos=gl_in[0].gl_Position.xyz+normalize(vec3(
			rand(vec2(pos.x,0.123)),
			rand(vec2(pos.y,0.123)),
			rand(vec2(pos.z,0.123))
	))*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos,1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	outPos=gl_in[0].gl_Position.xyz+normalize(vec3(
			rand(vec2(pos.x,0.456)),
			rand(vec2(pos.y,0.456)),
			rand(vec2(pos.z,0.456))
	))*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos,1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	outPos=gl_in[0].gl_Position.xyz+normalize(vec3(
			rand(vec2(pos.x,0.789)),
			rand(vec2(pos.y,0.789)),
			rand(vec2(pos.z,0.789))
	))*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos,1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	EndPrimitive();
	
	//prim 2
	outPos=gl_in[0].gl_Position.xyz+normalize(vec3(
			rand(vec2(pos.x,0.987)),
			rand(vec2(pos.y,0.987)),
			rand(vec2(pos.z,0.987))
	))*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos,1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	outPos=gl_in[0].gl_Position.xyz+normalize(vec3(
			rand(vec2(pos.x,0.654)),
			rand(vec2(pos.y,0.654)),
			rand(vec2(pos.z,0.654))
	))*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos,1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	outPos=gl_in[0].gl_Position.xyz+normalize(vec3(
			rand(vec2(pos.x,0.321)),
			rand(vec2(pos.y,0.321)),
			rand(vec2(pos.z,0.321))
	))*size;
	outPos=(MMatrix*vec4(outPos,1.0)).xyz;
	gl_Position=PMatrix*VMatrix*vec4(outPos,1.0);
	g2f_flag=v2g_flag[0];
	EmitVertex();
	
	EndPrimitive();
}
