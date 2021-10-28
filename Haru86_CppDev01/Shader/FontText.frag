#version 330

in vec2 uv;
in float time;
in vec2 resolution;

uniform sampler2D _fontTexture;

//out vec4 outColor;

void main(){
	vec4 col=vec4(uv.x,uv.y,0.0,1.0);
	col=texture(_fontTexture,1.0-uv);
	gl_FragColor=col;
}