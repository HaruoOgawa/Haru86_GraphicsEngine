#version 410

layout(vertices=4)out;

float outLevel=10.0;
float inLevel=10.0;

void main(){
	gl_out[gl_InvocationID].gl_Position=gl_in[gl_InvocationID].gl_Position;	

	gl_TessLevelOuter[0]=outLevel;
	gl_TessLevelOuter[1]=outLevel;
	gl_TessLevelOuter[2]=outLevel;
	gl_TessLevelOuter[3]=outLevel;
	
	gl_TessLevelInner[0]=inLevel;
	gl_TessLevelInner[1]=inLevel;

}