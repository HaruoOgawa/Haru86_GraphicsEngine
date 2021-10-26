precision mediump float;

in vec2 uv;
in float time;
in vec2 resolution;

uniform sampler2D frameTex;

void main(void){
	gl_FragColor=texture(frameTex,uv);
	//gl_FragColor=vec4(uv,0.,1.);
}