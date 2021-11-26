#version 430

layout(location=0)in vec3 vertex;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 texcoord;

struct AttribData{
	vec4 velocity;
};

layout(std430,binding=0) buffer destBuffer{
	AttribData data[];
};

uniform mat4 MVPMatrix;
uniform mat4 MMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform float _time;
uniform float _deltaTime;

#define PI 3.14159265
#define rot(a) mat2(cos(a),sin(a),-sin(a),cos(a))

 float rand(vec2 st)
{
    return fract(sin(dot(st, vec2(12.9898, 78.233))) * 43758.5453);
}

out vec2 uv;
out vec4 velocity;

void main(){
	vec3 pos=vec3(rand(vec2(gl_InstanceID,0.123))*2.0-1.0,
		rand(vec2(gl_InstanceID,0.456))*2.0-1.0,
		rand(vec2(gl_InstanceID,0.789))*2.0-1.0
	)*10.0;

	pos=(MMatrix*vec4(vertex,1.0)).xyz+pos;

	gl_Position=PMatrix*VMatrix*vec4(pos,1.0);
	velocity=data[gl_InstanceID].velocity;
	uv=texcoord;
}