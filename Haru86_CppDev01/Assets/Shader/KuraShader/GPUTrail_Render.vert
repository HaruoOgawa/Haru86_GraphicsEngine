#version 430

//BoidsData/////
struct BoidsData {
    vec3 position;
    vec3 velocity;
};

layout(std430,binding=1) buffer destBufferBoidsData
{
	BoidsData boidsData[];
} outBufferBoidsData;

// outBufferBoidsData.boidsData[].position

//input/////
 struct input_data{
    vec3 nextInputPosition;
};

layout(std430,binding=2) buffer destBuffer_input_data
{
	input_data iData[];
} outBuffer_input_data;

// outBuffer_input_data.iData[].nextInputPosition

//node/////
struct node{
    vec3 node_position;
    float node_life;
    int renderFlag;
};

layout(std430,binding=3) buffer destBuffer_node
{
	node nodes[];
} outBuffer_node;

//trail///////
struct trail{
    int nextCalNodeIndex;
    int leftSideFirst;
    int rightSideFirst;
    int rightSideSecond;
    vec4 trail_color;
};

layout(std430,binding=4) buffer destBuffer_trail
{
	trail trails[];
} outBuffer_trail;

////////////////////////

layout(location=0)in vec3 vertex;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 texcoord;

uniform float _time;
uniform float _deltaTime;
uniform int _boids_count;
uniform mat4 MVPMatrix;

out float v2g_flag;
out vec3 v2g_pos;

#define PI 3.14159265
#define rot(a) mat2(cos(a),sin(a),-sin(a),cos(a))

float rand(vec2 seeds){
  return fract(sin(dot(seeds, vec2(12.9898,78.233))) * 43758.5453);
}

//outBufferBoidsData.boidsData
// outBuffer_input_data.iData
//outBuffer_node.nodes
//outBuffer_trail.trails

void main(){
	vec3 pos=vec3(rand(vec2(gl_InstanceID,0.123))*2.0-1.0,
		rand(vec2(gl_InstanceID,0.456))*2.0-1.0,
		rand(vec2(gl_InstanceID,0.789))-0.1
	)*300.0;
	v2g_pos=pos;

	int id=gl_InstanceID;
	float flag=1.0;
	if(id>_boids_count/2+1){
		flag=0.0;
	}else{
		flag=1.0;
	}
	v2g_flag=flag;

	//gl_Position=vec4(vertex,1.0);
	gl_Position=MVPMatrix*vec4(vertex,1.0);
	
}