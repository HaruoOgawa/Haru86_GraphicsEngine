#version 330

in vec2 uv;
in vec3 CameraPos;
in vec3 WorldVertexPos;
in vec3 WorldNormal;

in float nv_vert;

out vec4 outColor;

void main(){
	vec3 col=vec3(0.0);

	if(abs(nv_vert) < 0.25){
		col.rgb=vec3(0.0);
	}else{	
		col.rgb=vec3(1.0);
	}

	outColor=vec4(col,1.0);
}