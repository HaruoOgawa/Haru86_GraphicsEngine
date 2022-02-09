#version 330

in vec2 uv;

out vec4 outColor;

void main(){
	vec2 st=fract(uv*100.0);
	st=st*2.0-1.0;

	vec3 col=vec3(1.0);
	float threshold=0.95;
	col=(abs(st.x)>threshold)? vec3(0.0) : col;
	col=(abs(st.y)>threshold)? vec3(0.0) : col;

	outColor=vec4(col,0.5);
}