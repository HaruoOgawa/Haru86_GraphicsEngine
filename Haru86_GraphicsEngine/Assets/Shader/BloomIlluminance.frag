#version 430

in vec2 uv;
in float time;
in vec2 resolution;

uniform sampler2D _SrcTexture;
uniform float _frameResolusion;
uniform float _BloomThreshold;
uniform float _BloomIntensity;

void main(){
	vec3 col=vec3(0.0); 
	col.rgb=texture(_SrcTexture,uv*_frameResolusion).rgb;

	// ‹P“x‚ðŒvŽZ
	col.rgb=max(col.rgb-_BloomThreshold,0.0)*_BloomIntensity;

	gl_FragColor=vec4(col,1.0);
}