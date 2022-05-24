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

	// 元の頂点のモデル座標系(グローバルポーズ) => Tポーズ型の親子関係を加味したジョイントの座標系(ローカルポーズ) => 次のポーズのモデル座標系(グローバルポーズ)
	// といったように座標系を変換していく必要がある
	// weightで影響の度合いを調整
	mat4 skin=(pose[int(joints.x)]*invBindPose[int(joints.x)])*weights[int(joints.x)];
	skin+=(pose[int(joints.y)]*invBindPose[int(joints.y)])*weights[int(joints.y)];
	skin+=(pose[int(joints.z)]*invBindPose[int(joints.z)])*weights[int(joints.z)];
	skin+=(pose[int(joints.w)]*invBindPose[int(joints.w)])*weights[int(joints.w)];

	vec4 pos=vec4(vertex,1.0);
	//pos=skin*pos;
	gl_Position=MVPMatrix*pos;
	uv=texcoord;
	CameraPos=_CameraPos;
	WorldVertexPos=(MMatrix*skin*pos).xyz;
	WorldNormal=(MMatrix*skin*vec4(normal,0.0)).xyz;
}