#version 430

precision highp float;

in vec2 uv;
in float time;
in vec2 resolution;

uniform sampler2D _IlluminanceTexture;
uniform float _frameResolusion;
uniform vec2 _resolution;

void main(){
	vec3 col=vec3(0.0); 
	vec2 texelSize=1.0/_resolution.xy;
	
	int fSize=4;

	for(int x=-fSize;x<=fSize;x++){
		for(int y=-fSize;y<=fSize;y++){
			vec2 st= uv+vec2(
				texelSize.x*float(x),
				texelSize.y*float(y)
			);
			col+=texture(_IlluminanceTexture,st*_frameResolusion).rgb;

		}
	}

	col/=pow(fSize*2+1,2.0);

	//col.rgb=texture(_IlluminanceTexture,uv*_frameResolusion).rgb;
	
	gl_FragColor=vec4(col,1.0);
}