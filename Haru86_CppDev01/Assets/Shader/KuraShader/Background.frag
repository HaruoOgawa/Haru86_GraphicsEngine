#version 330

in vec2 uv;

uniform sampler2D _backgroundTex;

void main(){
	vec4 col=vec4(1.0);
	//col=vec4(uv.x,uv.y,0.0,1.0);
	col=texture(_backgroundTex,uv);
	gl_FragColor=col;
}