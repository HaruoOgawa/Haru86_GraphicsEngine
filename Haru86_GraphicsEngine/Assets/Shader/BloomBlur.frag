#version 430

precision highp float;

in vec2 uv;
in float time;
in vec2 resolution;

uniform sampler2D _IlluminanceTexture;
uniform float _frameResolusion;
uniform vec2 _resolution;
uniform float _weights[10];

void main(){
	vec3 col=vec3(0.0); 
	vec2 texelSize=1.0/_resolution.xy;
	//texelSize/=_frameResolusion;
	//texelSize*=2.0;

	int fSize=10;

	// ガウシアンブラーの実装

	// x blur
	col+=texture(_IlluminanceTexture,uv*_frameResolusion).rgb*_weights[0];
	for(int i=1;i<fSize;i++){
		col+=texture(_IlluminanceTexture,( uv+vec2(texelSize.x*float(i),0.0))*_frameResolusion).rgb*_weights[i];
		col+=texture(_IlluminanceTexture,( uv-vec2(texelSize.x*float(i),0.0))*_frameResolusion).rgb*_weights[i];
	}

	// y blur
	col+=texture(_IlluminanceTexture,uv*_frameResolusion).rgb*_weights[0];
	for(int i=1;i<fSize;i++){
		col+=texture(_IlluminanceTexture,( uv+vec2(0.0,texelSize.y*float(i)))*_frameResolusion).rgb*_weights[i];
		col+=texture(_IlluminanceTexture,( uv-vec2(0.0,texelSize.y*float(i)))*_frameResolusion).rgb*_weights[i];
	}

	//col.rgb=texture(_IlluminanceTexture,uv*_frameResolusion).rgb;
	
	gl_FragColor=vec4(col,1.0);
}