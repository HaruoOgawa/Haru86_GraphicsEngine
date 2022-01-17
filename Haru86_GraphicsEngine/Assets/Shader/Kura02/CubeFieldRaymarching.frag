#version 430

uniform vec2 _resolution;

void main(){
	vec2 st=gl_FragCoord.xy/_resolution.xy;
	vec3 col=vec3(1.0);
	col=vec3(st,0.0);
	gl_FragColor=vec4(col,1.0);
}