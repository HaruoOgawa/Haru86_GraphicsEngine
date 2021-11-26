#version 430

in vec2 uv;
in vec4 velocity;

void main(){
	//gl_FragColor=vec4(uv,0.0,1.0);
	gl_FragColor=velocity;
}
