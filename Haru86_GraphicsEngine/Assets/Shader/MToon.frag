#version 330

in vec2 uv;
in vec3 CameraPos;
in vec3 WorldVertexPos;
in vec3 WorldNormal;

out vec4 outColor;

void main(){
	vec3 col=vec3(0.0);

	vec3 ldir=normalize(vec3(0.0,-1.0,1.0));
	float ln=max(0.0,dot(ldir,normalize(WorldNormal)));

	col=vec3(1.0)*ln;

	outColor=vec4(col,1.0);
}