#version 410

in float pid;
in vec3 t2f_normal;

#define LightDir vec3(-0.613121, -0.1916, 0.766402)

float rand(vec2 seeds){
  return fract(sin(dot(seeds, vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
	vec4 col=vec4(1.0);
	
	col.rgb=(int(pid)%2==0)?vec3(1.0,0.0,0.0):vec3(0.0,0.0,1.0);

	float diff=max(dot(normalize(t2f_normal),normalize(LightDir)),0.0);
	//col.rgb*=diff;


	gl_FragColor=col;
}