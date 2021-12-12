#version 410

layout(quads) in;

uniform mat4 MVPMatrix;
uniform mat4 MMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform float _time;
uniform float _deltaTime;

in vec3 tesc2tese_normal[];

out float pid;
out vec3 t2f_normal;

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
    vec2 g00 = normalize(-1 + 2 * random2(i00));
    vec2 g10 = normalize(-1 + 2 * random2(i10));
    vec2 g01 = normalize(-1 + 2 * random2(i01));
    vec2 g11 = normalize(-1 + 2 * random2(i11));
    float v00 = dot(g00, f00);
    float v10 = dot(g10, f10);
    float v01 = dot(g01, f01);
    float v11 = dot(g11, f11);
    vec2 p = smoothstep(0, 1, f);
    float v00v10 = mix(v00, v10, p.x);
    float v01v11 = mix(v01, v11, p.x);
    return mix(v00v10, v01v11, p.y) * 0.5 + 0.5;
}


void main(){
	float u=gl_TessCoord.x;
	float v=gl_TessCoord.y;

	vec4 v0=gl_in[0].gl_Position;
	vec4 v1=gl_in[1].gl_Position;
	vec4 v2=gl_in[2].gl_Position;
	vec4 v3=gl_in[3].gl_Position;

    vec3 normal=normalize(
         tesc2tese_normal[0]*(1.0-u)*(1.0-v) +
         tesc2tese_normal[1]*u*(1.0-v) + 
         tesc2tese_normal[2]*u*v  + 
         tesc2tese_normal[3]*(1.0-u)*v
    );
    t2f_normal=normal;

	vec4 pos= v0*(1.0-u)*(1.0-v) + v1*u*(1.0-v) +v2*u*v  + v3*(1.0-u)*v;
	//vec4 pos= v0*gl_TessCoord.x + v1*gl_TessCoord.y +v2*gl_TessCoord.z ;

	//pos.z+=sin(_time*0.01+float(gl_TessCoord.x+gl_TessCoord.y)*100.0)*1.0;
	pos.y+=perlinNoise(gl_TessCoord.xy*100.0+vec2(0.123,_time*0.001))*0.5;

    gl_Position=MVPMatrix*pos;
	
	pid=float(gl_PrimitiveID);
}