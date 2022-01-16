#version 430

uniform vec3 _CameraPosition;
uniform vec3 _lightDir;

in vec3 worldPosition;
in vec3 worldNormal;

void main(){
	vec3 col=vec3(1.0);

	//diffuse
	vec3 L=normalize(_lightDir);
	float diff=max(0.0,dot(worldNormal,L));
	col.rgb*=diff;
	col+=0.05;

	gl_FragColor=vec4(col,0.5);
}