#version 330

uniform mat4 MVPMatrix;
uniform mat4 MMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform float _time;
uniform float _deltaTime;
uniform vec3 _CameraPos;

uniform mat4 pose[120];
uniform mat4 invBindPose[120];

layout(location=0)in vec3 vertex;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 texcoord;
layout(location=3)in vec4 weights;
layout(location=4)in ivec4 joints;

out vec2 uv;
out vec3 CameraPos;
out vec3 WorldVertexPos;
out vec3 WorldNormal;

#define rot(a) mat2(cos(a),-sin(a),sin(a),cos(a))

void main(){
	mat4 skin=(pose[joints.x]*invBindPose[joints.x])*weights[joints.x];
	skin+=(pose[joints.y]*invBindPose[joints.y])*weights[joints.y];
	skin+=(pose[joints.z]*invBindPose[joints.z])*weights[joints.z];
	skin+=(pose[joints.w]*invBindPose[joints.w])*weights[joints.w];

	vec4 pos=vec4(vertex,1.0);
	gl_Position=MVPMatrix*skin*pos;
	uv=texcoord;
	CameraPos=_CameraPos;
	WorldVertexPos=(MMatrix*skin*pos).xyz;
	WorldNormal=(MMatrix*skin*vec4(normal,0.0)).xyz;
}