#version 430

in vec2 g2f_uv;
in vec4 g2f_velocity;
in vec3 g2f_randCol;

void main(){
	vec4 col=vec4(1.0);
	col=vec4(exp(-10.0*length(g2f_uv*2.0-1.0)));
	col.a=(col.a<0.5)? 0.0 : col.a;
	col.rgb*=g2f_randCol;

	col.rgb=g2f_velocity.xyz;

	col=vec4(g2f_uv,0.0,1.0);

	gl_FragColor=col;
}
