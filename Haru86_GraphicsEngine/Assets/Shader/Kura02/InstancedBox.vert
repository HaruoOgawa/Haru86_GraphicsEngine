#version 430

uniform mat4 MVPMatrix;
uniform mat4 MMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform float _time;
uniform float _deltaTime;
uniform int _instancedCound;
uniform int _sideCubeCount;
uniform float _cubeWidth;

layout(location=0)in vec3 vertex;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 texcoord;

struct SCubeFieldObj
{
    int xIndex;
    int yIndex;
    int instancedIndex;
};

layout(std430,binding=0) buffer destBufferCubeFieldObj
{
	SCubeFieldObj cubeObj[];
} outBufferCubeFieldObj;

// outBufferCubeFieldObj.cubeObj[]

out vec3 worldPosition;
out vec3 worldNormal;

#define rot(a) mat2(cos(a),-sin(a),sin(a),cos(a))
#define PI 3.14159265

float rand(vec2 seeds){
  return fract(sin(dot(seeds, vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
	
	
	mat4x4 ModelMatrix=
		mat4x4(
			vec4(_cubeWidth,0.0,0.0,0.0),
			vec4(0.0,_cubeWidth,0.0,0.0),
			vec4(0.0,0.0,_cubeWidth,0.0),
			vec4(0.0,0.0,0.0,1.0)
		);

	vec3 pos=(ModelMatrix*vec4(vertex,1.0)).xyz;

	SCubeFieldObj objData=outBufferCubeFieldObj.cubeObj[gl_InstanceID];
	float xVal=_cubeWidth*float(_sideCubeCount)*(objData.xIndex/float(_sideCubeCount-1))*2.0-_cubeWidth*float(_sideCubeCount);
	float zVal=_cubeWidth*float(_sideCubeCount)*(objData.yIndex/float(_sideCubeCount-1))*2.0-_cubeWidth*float(_sideCubeCount);
	
	float yVal=-5.0;
	vec2 st=(vec2(float(objData.xIndex),float(objData.yIndex))/float(_sideCubeCount))*2.0-1.0;
	yVal+=sin(-_time*0.005+length(st)*25.0)*max(1.0,length(st)*2.0);

	float adjustPos=0.6;
	pos+=vec3(xVal*adjustPos,yVal,zVal*adjustPos);

	gl_Position=PMatrix*VMatrix*vec4(pos,1.0);
	worldPosition=pos;
	worldNormal=normalize((ModelMatrix*vec4(normal,1.0)).xyz);
}