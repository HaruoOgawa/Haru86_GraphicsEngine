#version 410

layout(quads) in;

uniform mat4 MVPMatrix;
uniform mat4 MMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform float _time;
uniform float _deltaTime;

void main(){
	float u=gl_TessCoord.x;
	float v=gl_TessCoord.y;

	vec4 v0=gl_in[0].gl_Position;
	vec4 v1=gl_in[1].gl_Position;
	vec4 v2=gl_in[2].gl_Position;
	vec4 v3=gl_in[3].gl_Position;

	vec4 pos= v0*(1.0-u)*(1.0-v) + v1*u*(1.0-v)
                 +v2*u*v  + v3*(1.0-u)*v;
	gl_Position=MVPMatrix*pos;

}