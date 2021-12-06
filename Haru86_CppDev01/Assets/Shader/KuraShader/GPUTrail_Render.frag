#version 430

in float g2f_flag;

#define LightDir vec3(-0.613121, -0.1916, 0.766402)

void main(){
	vec4 col=vec4(1.0);
	col.rgb=vec3(0.0);

	float flag=g2f_flag;
	if(flag==0.0){
		discard;
	}

	gl_FragColor=col;
}
