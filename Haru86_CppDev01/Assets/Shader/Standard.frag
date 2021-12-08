#version 330

in vec2 uv;

out vec4 outColor;

uniform sampler2D _brush_pow2;

void main(){
	//outColor=vec4(uv.x,uv.y,0.0,1.0);
	outColor=texture(_brush_pow2,uv);
}