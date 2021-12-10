precision mediump float;

in vec2 uv;
in float time;
in vec2 resolution;

uniform sampler2D frameTex;
uniform float _frameResolusion;
uniform float _postProcessFlag;
uniform float _postProcessVal;

#define PI 3.14159265

float rand(vec2 seeds){
  return fract(sin(dot(seeds, vec2(12.9898,78.233))) * 43758.5453);
}

void main(void){
	vec4 col=vec4(0.,0.,0.,1.);
	col.rgb=texture(frameTex,uv*_frameResolusion);
	vec2 st=uv;
	st=2.0*st-1.0;
	float width=0.4;
	col.rgb*=(abs(st.y)>1.0-width)? 0.0:1.0;
	
	gl_FragColor=col;
}
