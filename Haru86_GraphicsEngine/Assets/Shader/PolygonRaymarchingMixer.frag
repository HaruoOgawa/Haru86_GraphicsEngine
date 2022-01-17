#version 430

uniform float _frameResolusion;

uniform sampler2D polygon_frameTexture;
uniform sampler2D polygon_depthTexture;
uniform sampler2D raymarching_frameTexture;
uniform sampler2D raymarching_depthTexture;

in vec2 uv;

void main(){
	vec3 col=vec3(uv,1.0);

	/*vec2 st=uv;
	if(uv.x<=0.5&&uv.y<=0.5){
		st.x*=2.0;
		st.y*=2.0;
		col=texture(polygon_depthTexture,st*_frameResolusion).rgb;
	}else if(uv.x<=0.5&&uv.y>0.5){
		st.x*=2.0;
		st.y*=2.0-1.0;
		col=texture(polygon_frameTexture,st*_frameResolusion).rgb;
	}else if(uv.x>0.5&&uv.y<=0.5){
		st.x*=2.0-1.0;
		st.y*=2.0;
		col=texture(raymarching_depthTexture,st*_frameResolusion).rgb;
	}else if(uv.x>0.5&&uv.y>0.5){
		st.x*=2.0-1.0;
		st.y*=2.0-1.0;
		col=texture(raymarching_frameTexture,st*_frameResolusion).rgb;
	}*/

	//col=texture(raymarching_frameTexture,uv*_frameResolusion).rgb;

	//polygon
	vec3 polygonCol=texture(polygon_frameTexture,uv*_frameResolusion).rgb;
	vec3 polygonDepth=texture(polygon_depthTexture,uv*_frameResolusion).rgb;
	//raymarching
	vec3 raymarchingCol=texture(raymarching_frameTexture,uv*_frameResolusion).rgb;
	vec3 raymarchingDepth=texture(raymarching_depthTexture,uv*_frameResolusion).rgb;

	col=(polygonDepth.r<=raymarchingDepth.r)? polygonCol : raymarchingCol;

	//col=raymarchingDepth;

	gl_FragColor=vec4(col,1.0);
}
