#version 330

uniform mat4 mMatrix;
uniform mat4 vpMatrix;

layout(location=0)in vec3 vertex;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 texcoord;

out vec2 uv;

void main(){
	vec4 pos=vec4(vertex,1.0);
	gl_Position=vpMatrix*mMatrix*pos;
	uv=texcoord;
}