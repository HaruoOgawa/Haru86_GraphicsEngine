#version 430

in vec2 g2f_uv;
in vec3 g2f_randCol;
in vec3 g2f_normal;

//uniform sampler2D _PosTex;
//uniform sampler2D _NormalTex;

#define LightDir vec3(-0.613121, -0.1916, 0.766402)

void main(){
	vec4 col=vec4(1.0);
	//col=vec4(g2f_normal,1.0);
	
	float diff=max(dot(normalize(g2f_normal),normalize(LightDir)),0.0);
	col.rgb*=diff;
	col.rgb+=vec3(0.25);
	col.rgb*=g2f_randCol;

	//col.rgb=texture(_NormalTex,g2f_uv).rgb;
	//col.rgb=vec3(g2f_uv,0.0);

	gl_FragColor=col;
}
