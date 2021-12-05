#version 430

in vec2 g2f_uv;
in vec3 g2f_randCol;
in vec3 g2f_normal;
in float g2f_flag;

//uniform sampler2D _PosTex;
//uniform sampler2D _NormalTex;

#define LightDir vec3(-0.613121, -0.1916, 0.766402)

void main(){
	vec4 col=vec4(0.25);
	col.rgb=vec3(0.0);

	float flag=g2f_flag;
	//col.a=flag;
	if(flag==0.0){
		discard;
	}

	float diff=max(dot(normalize(g2f_normal),normalize(LightDir)),0.0);
	//col.rgb*=diff;
	//col.rgb+=vec3(0.25);
	//col.rgb*=g2f_randCol;

	gl_FragColor=col;
}
