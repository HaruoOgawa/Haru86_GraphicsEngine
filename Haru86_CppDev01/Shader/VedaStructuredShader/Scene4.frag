
precision mediump float;

uniform float time;
uniform vec2 resolution;
uniform vec2 uv;
/*
in vec2 uv;
in float time;
in vec2 resolution;
*/
uniform float _cameraPositionIndex;

#define rot(a) mat2(cos(a),sin(a),-sin(a),cos(a))
#define PI 3.14159265

struct DBuffer{
  float d1;
  float d2;
  float d3;
  float mainD;
};

struct AccBuffer{
  float acc1;
  float acc2;
  float acc3;
};

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

vec2 fmod(vec2 p,float r){
  float a=atan(p.x,p.y)+PI/r;
  float n=(2.*PI)/r;
  a=floor(a/n)*n;
  return rot(a)*p;
}

float Plane(vec3 p){
  float d=-p.y+1.0;
  d=min(d,p.y+1.0);

  return d;
}

float Cube(vec3 p,vec3 s){
  return length(max(abs(p)-s,0.0));
}

float d1(vec3 p){
  p.z-=time;
  p.y+=perlinNoise(vec2(p.x,p.z))+perlinNoise(vec2(p.x,p.z)*5.0)*0.5+perlinNoise(vec2(p.x,p.z)*10.0)*0.35;
  p.y*=0.6;
  p.y=p.y*2.0-1.0;
  float d=Plane(p);
      return d;
}

float d2(vec3 p){
p.z-=time;
//p.xy*=rot(time);
//p.xz*=rot(time);
//p.yz*=rot(time);
  vec3 pos0=p;
  float r=perlinNoise(vec2(pos0.x,pos0.z))+perlinNoise(vec2(pos0.x,pos0.y)*5.0)*0.5+perlinNoise(vec2(pos0.y,pos0.z)*10.0)*0.35;
float k=2.1;
pos0=mod(pos0,k)-k*0.5;

  //float d=Cube(pos0,vec3(0.5,0.5,0.5));
  float d=length(pos0)-r;

  return d;
}
DBuffer map(vec3 p){
  DBuffer d;
  d.d1=d1(p);
  //d.d1=2000.0;
  d.d2=d2(p);
  //d.d2=d2(p);
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

vec3 hsv2rgb2(vec3 c, float k) {
    return smoothstep(0. + k, 1. - k,
        .5 + .5 * cos((vec3(c.x, c.x, c.x) + vec3(3., 2., 1.) / 3.) * radians(360.)));
}

void main(void) {
  vec2 st = (gl_FragCoord.xy*2.0-resolution.xy) / min(resolution.x,resolution.y);
  //vec2 st=uv*2.0-1.0;
  //st.x*=(resolution.x/resolution.y);

  vec3 col=vec3((st.y+1.0)*0.5*0.25);
  float radius=15.;
float speed=-.25;
 vec3 ta=vec3(0.);
 vec3 ro=vec3(0.,0.,2.);
 float adjustAcc=0.5;
//vec3 ro=vec3(cos(time),0.0,sin(time));

 vec3 cDir=normalize(ta-ro);
 vec3 cSide=normalize(cross(cDir,vec3(0.,-1.,0.)));
 vec3 cUp=normalize(cross(cDir,cSide));
 float depth=1.;
 vec3 rd=normalize(vec3(st.x*cSide+st.y*cUp+cDir*depth));

  DBuffer d;
  AccBuffer acc;
  float t=0.0;
  for(int i=0;i<128;i++){
    d=map(ro+rd*t);
    if(d.d1<0.001||d.d2<0.001||d.d3<0.001||t>1000.0)break;
    t+=d.mainD*.5;

    acc.acc1+=exp(-6.0*(d.d2));
    acc.acc2+=exp(-6.0*d.d2);
    acc.acc3+=exp(-1.0*d.mainD);
  }

    if(d.d1<0.001){

    col+=vec3(exp(-.1*t))*vec3(0.,0.25,1.0)*acc.acc1*0.025;
    }

    if(d.d2<0.001){
      col+=vec3(exp(-.25*t))*vec3(0.,0.25,1.0)*acc.acc2*0.025;
    }


  gl_FragColor = vec4(col, 1.0);
}
