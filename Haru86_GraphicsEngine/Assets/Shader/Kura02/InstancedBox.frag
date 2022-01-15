#version 330

uniform vec3 _CameraPosition;

void main(){
	vec3 col=vec3(1.0);
	gl_FragColor=vec4(col,0.5);
}