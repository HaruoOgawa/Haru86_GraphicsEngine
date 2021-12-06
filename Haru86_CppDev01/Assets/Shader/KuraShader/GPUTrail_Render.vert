#version 430

layout(location=0)in vec3 vertex;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 texcoord;

uniform mat4 MVPMatrix;
uniform mat4 MMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform float _time;
uniform float _deltaTime;
uniform int _boids_count;

out float v2g_flag;

#define PI 3.14159265
#define rot(a) mat2(cos(a),sin(a),-sin(a),cos(a))

float rand(vec2 seeds){
  return fract(sin(dot(seeds, vec2(12.9898,78.233))) * 43758.5453);
}
void main(){
	vec3 pos=vec3(rand(vec2(gl_InstanceID,0.123))*2.0-1.0,
		rand(vec2(gl_InstanceID,0.456))*2.0-1.0,
		rand(vec2(gl_InstanceID,0.789))-0.1
	)*300.0;

	int id=gl_InstanceID;
	float flag=1.0;
	if(id>_boids_count/2+1){
		flag=0.0;
	}else{
		flag=1.0;
	}
	v2g_flag=flag;

	vec3 vert=vertex;
	vert+=pos;
	gl_Position=PMatrix*VMatrix*vec4(vert,1.0);
	
	
}