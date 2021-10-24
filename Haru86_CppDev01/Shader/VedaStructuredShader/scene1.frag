precision mediump float;
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

#define rot(a) mat2(cos(a),sin(a),-sin(a),cos(a))

struct DBuffer{
  float d1;
  float d2;
  float d3;
  float mainD;
};

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

float Plane(vec3 p){
p.z-=time;
p.y+=perlinNoise(p.xz)+perlinNoise(p.zx*3.);
  return p.y;
}

float d1(vec3 p){
  //p.z+=time;
  //p=mod(p,2.0)-1.0;
  float d=Plane(p);
  return d;
}

DBuffer map(vec3 p){
  DBuffer d;
  d.d1=d1(p);
  d.d2=2000.0;
  d.d3=2000.0;
  d.mainD=min(min(d.d1,d.d2),d.d3);
  return d;
}

vec3 gn(vec3 p){
  vec2 e=vec2(0.001,0.);
  return normalize(
    vec3(
      map(p+e.xyy).mainD-map(p-e.xyy).mainD,
      map(p+e.yxy).mainD-map(p-e.yxy).mainD,
      map(p+e.yyx).mainD-map(p-e.yyx).mainD
      )
    );
}

void main(void) {
  vec2 st = (gl_FragCoord.xy*2.0-resolution.xy) / min(resolution.x,resolution.y);
  vec3 col=vec3(0.,0.,0.);
  vec3 ro=vec3(0.,.05,1.0);
  vec3 rd=normalize(vec3(st,-1.0));

  DBuffer d;
  float t,acc=0.0;
  for(int i=0;i<64;i++){
    d=map(ro+rd*t);
    if(d.mainD<0.001||t>1000.0)break;
    t+=d.mainD*0.8;
    acc+=exp(-3.0*d.mainD);
  }

  vec3 n=gn(ro+rd*t);

  col=vec3(exp(-.5*t))*vec3(0.45,0.25,0.16)*acc*0.25;

  gl_FragColor = vec4(col, 1.0);
}
