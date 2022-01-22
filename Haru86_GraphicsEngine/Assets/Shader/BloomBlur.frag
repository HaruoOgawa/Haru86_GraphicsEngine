#version 430

in vec2 uv;
in float time;
in vec2 resolution;

uniform sampler2D _IlluminanceTexture;
uniform float _frameResolusion;
uniform vec2 _resolution;

void main(){
	vec3 col=vec3(0.0); 
	vec2 texelSize=1.0/_resolution.xy;

	for(int x=-1;x<1;x++){
		for(int y=-1;y<1;y++){
			vec2 st=uv+vec2(x*texelSize.x,y*texelSize.y);
			col+=texture(_IlluminanceTexture,st*_frameResolusion).rgb;
		}
	}
	
	col/=9.0;

	//col.rgb=texture(_IlluminanceTexture,uv*_frameResolusion).rgb;
	
	gl_FragColor=vec4(col,1.0);
}