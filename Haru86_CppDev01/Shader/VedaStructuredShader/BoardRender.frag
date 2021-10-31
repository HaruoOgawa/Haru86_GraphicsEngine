precision mediump float;

in vec2 uv;
in float time;
in vec2 resolution;

uniform sampler2D frameTex;
uniform float _frameResolusion;
uniform float _postProcessFlag;

void main(void){
	vec4 col=vec4(0.,0.,0.,1.);
	
	if(_postProcessFlag==0){
		col.rgb=texture(frameTex,uv*_frameResolusion);
	}
	else if(_postProcessFlag==1){
		float _Strength=1.0;
		int _SampleCount=3;
		vec2 symmetryUv    = uv - 0.5;
		float distance       = length(symmetryUv);
		float factor         = _Strength / _SampleCount * distance;
		for(int j = 0; j < _SampleCount; j++) {
			float uvOffset       = 1 - factor * j;
			col                 += texture(frameTex, (symmetryUv * uvOffset + 0.5)*_frameResolusion);
		}
		col                 /= _SampleCount;
	}else if(_postProcessFlag==2){
				uv.y+=0.05*sin(time*100.0);
				uv.x+=0.01*sin(time*50.0);

				vec4 _GapOffsetX=vec4(1.0,0.5,0.25,0.0);
				vec4 _GapOffsetY=vec4(0.02,0.03,0.03,0.0);
				float _gapOffsetPower=0.08;
				
				vec2 vecFromCenter=vec2(0.0,0.0)-(uv-vec2(0.5,0.5))*2.0;

                vec2 st_R=uv+vecFromCenter*_gapOffsetPower*_GapOffsetX.r;
                vec2 st_G=uv+vecFromCenter*_gapOffsetPower*_GapOffsetX.g;
                vec2 st_B=uv+vecFromCenter*_gapOffsetPower*_GapOffsetX.b;

                col.rgb=texture(frameTex,uv*_frameResolusion);
                col.r+=texture(frameTex,st_R*_frameResolusion);
                col.g+=texture(frameTex,st_G*_frameResolusion);
                col.b+=texture(frameTex,st_B*_frameResolusion);
	}else if(_postProcessFlag==4){
				uv.y+=0.05*sin(time*100.0);
				uv.x+=0.01*sin(time*50.0);

				vec4 _GapOffsetX=vec4(1.0,0.5,0.25,0.0);
				vec4 _GapOffsetY=vec4(0.02,0.03,0.03,0.0)*6.0;
				float _gapOffsetPower=0.08*(sin(time*0.5)+1.0)*0.5;
				
				vec2 vecFromCenter=vec2(0.0,0.0)-(uv-vec2(0.5,0.5))*2.0;

                vec2 st_R=uv+vecFromCenter*_gapOffsetPower*_GapOffsetX.r;
                vec2 st_G=uv+vecFromCenter*_gapOffsetPower*_GapOffsetX.g;
                vec2 st_B=uv+vecFromCenter*_gapOffsetPower*_GapOffsetX.b;

                col.rgb=texture(frameTex,uv*_frameResolusion);
                col.r+=texture(frameTex,st_R*_frameResolusion);
                col.g+=texture(frameTex,st_G*_frameResolusion);
                col.b+=texture(frameTex,st_B*_frameResolusion);
	}else if(_postProcessFlag==3){
		col.rgb=texture(frameTex,uv*_frameResolusion);
		col.rgb=1.0-col.rgb;
	}
	
	gl_FragColor=col;
}
