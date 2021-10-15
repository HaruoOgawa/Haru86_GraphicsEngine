#version 330

uniform mat4 MVPMatrix;
uniform float _time;
uniform float _deltaTime;

layout(location=0)in vec3 vertex;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 texcoord;

out vec2 uv;

#define rot(a) mat2(cos(a),-sin(a),sin(a),cos(a))

void main(){
	vec4 pos=vec4(vertex,1.0);
	pos.xz*=rot(_time*0.005);
	pos.xy*=rot(_time*0.005);
	
	gl_Position=MVPMatrix*pos;
	uv=texcoord;
}