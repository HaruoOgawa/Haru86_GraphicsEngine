#version 410

in float pid;

float rand(vec2 seeds){
  return fract(sin(dot(seeds, vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
	vec4 col=vec4(1.0);
	col.rgb=(int(pid)%2==0)?vec3(1.0,0.0,0.0):vec3(0.0,0.0,1.0);
	col.r=rand(vec2(pid,0.951));
	/*col=vec4(
		rand(vec2(pid,0.951)),
		rand(vec2(pid,0.321)),
		rand(vec2(pid,0.123)),
	,1.0);*/

	gl_FragColor=col;
}