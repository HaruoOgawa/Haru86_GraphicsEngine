#version 330

uniform mat4 MVPMatrix;
uniform mat4 MMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform float _time;
uniform float _deltaTime;


layout(location=0)in vec3 vertex;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 texcoord;

float rand(vec2 seeds){
  return fract(sin(dot(seeds, vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
	vec3 pos=(MMatrix*vec4(vertex*(rand(vec2(0.974,gl_InstanceID*1000.0))+0.5)*2.0,1.0)).xyz;
	pos+=vec3(
		rand(vec2(gl_InstanceID*1000.0,0.651))*2.0-1.0,

		rand(vec2(gl_InstanceID*1000.0,0.159))*2.0-1.0
	)*10.0;
	//pos.xy=(length(pos.xy)<4.0)? pos.xy+pos.xy*1.5 : pos.xy;
	pos.z=mod(pos.z-_time*0.001,10.0)-10.0*0.5;
	gl_Position=PMatrix*VMatrix*vec4(pos,1.0);
}