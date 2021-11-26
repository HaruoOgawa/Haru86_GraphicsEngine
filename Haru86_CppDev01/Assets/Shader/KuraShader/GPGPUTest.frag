#version 430

in vec2 uv;
in vec4 velocity;
in vec3 randCol;

void main(){
	vec4 col=vec4(1.0);
	col=vec4(exp(-10.0*length(uv*2.0-1.0)));
	col.a=(col.a<0.5)? 0.0 : col.a;
	col.rgb*=randCol;
	gl_FragColor=col;
	//gl_FragColor=velocity;
}
