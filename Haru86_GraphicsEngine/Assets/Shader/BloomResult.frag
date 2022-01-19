#version 430

in vec2 uv;
in float time;
in vec2 resolution;

uniform sampler2D _BlurTexture;

void main(){
	vec3 col=vec3(0.0); 
	gl_FragColor=vec4(col,1.0);
}