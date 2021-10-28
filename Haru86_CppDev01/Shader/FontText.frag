#version 330

in vec2 uv;

uniform sampler2D _fontTexture;

out vec4 outColor;

void main(){
	outColor=vec4(uv.x,uv.y,0.0,1.0);
}