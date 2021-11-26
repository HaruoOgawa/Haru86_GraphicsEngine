#version 430

layout(location=0)in vec3 vertex;
layout(location=1)in vec3 normal;
layout(location=2)in vec2 texcoord;

struct AttribData{
	vec4 velocity;
};

layout(std430,binding=0) buffer destBuffer{
	AttribData data[];
} outBuffer;

uniform mat4 MVPMatrix;
uniform mat4 MMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform float _time;
uniform float _deltaTime;

#define PI 3.14159265
#define rot(a) mat2(cos(a),sin(a),-sin(a),cos(a))

float rand(vec2 seeds){
  return fract(sin(dot(seeds, vec2(12.9898,78.233))) * 43758.5453);
}

vec2 random2(vec2 seeds)
{
 seeds = vec2(dot(seeds, vec2(127.1, 311.7)),
 dot(seeds, vec2(269.5, 183.3)));
 return fract(sin(seeds) * 43758.5453123);
}

float perlinNoise(vec2 seeds)
{
vec2 i = floor(seeds);
vec2 f = fract(seeds);
vec2 i00 = i + vec2(0, 0);
vec2 i10 = i + vec2(1, 0);
vec2 i01 = i + vec2(0, 1);
vec2 i11 = i + vec2(1, 1);
vec2 f00 = f - vec2(0, 0);
vec2 f10 = f - vec2(1, 0);
vec2 f01 = f - vec2(0, 1);
vec2 f11 = f - vec2(1, 1);
vec2 g00 = normalize(-1.0 + 2.0 * random2(i00));
vec2 g10 = normalize(-1.0 + 2.0 * random2(i10));
vec2 g01 = normalize(-1.0 + 2.0* random2(i01));
vec2 g11 = normalize(-1.0 + 2.0* random2(i11));
float v00 = dot(g00, f00);
float v10 = dot(g10, f10);
float v01 = dot(g01, f01);
float v11 = dot(g11, f11);
vec2 p = smoothstep(0.0, 1.0, f);
float v00v10 = mix(v00, v10, p.x);
float v01v11 = mix(v01, v11, p.x);
return mix(v00v10, v01v11, p.y) * 0.5 + 0.5;
}

out vec2 uv;
out vec4 velocity;
out vec3 randCol;

void main(){
	vec3 pos=vec3(rand(vec2(gl_InstanceID,0.123))*2.0-1.0,
		rand(vec2(gl_InstanceID,0.456))*2.0-1.0,
		rand(vec2(gl_InstanceID,0.789))*2.0-1.0
	)*10.0;

	//pos.y+=sin(_time*0.001);
	float k=10.0;
	pos.y=mod(pos.y-gl_InstanceID-_time*0.0025,k)-k*0.5;

	pos=pos+vec3(
		(perlinNoise(vec2(_time*0.0001,gl_InstanceID*100.0))*2.0-1.0)*k*0.75,
		0.0,
		(perlinNoise(vec2(gl_InstanceID*100.0,_time*0.0001))*2.0-1.0)*k*0.75
	);

	pos=(MMatrix*vec4(vertex,1.0)).xyz+pos;

	gl_Position=PMatrix*VMatrix*vec4(pos,1.0);
	velocity=outBuffer.data[gl_InstanceID].velocity;
	uv=texcoord;
	randCol=vec3(rand(vec2(gl_InstanceID*100.0,0.987)),
		rand(vec2(gl_InstanceID*100.0,0.654)),
		rand(vec2(gl_InstanceID*100.0,0.321))
	);
}