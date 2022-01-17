#version 430

precision mediump float;

uniform vec2 _resolution;
uniform float _RenderingTarget;
uniform float _time;

in vec2 uv;

#define rot(a) mat2(cos(a),-sin(a),sin(a),cos(a))

float Cube(vec3 p,vec3 s){
  p=abs(p);
  return length(max(p-s,0.0));
}

float map(vec3 p){
  p.z-=_time;

  float k=2.5;
  vec3 p0=p;
p0=mod(p0,k)-k*0.5;
  for(int i=0;i<3;i++){
    p0=abs(p0)-.5;
    p0.xz*=rot(1.5);
    p0.xy*=rot(0.25);
    p0.yz*=rot(0.5);
    p0.z=abs(p0.z)-.85;
  }

  float d0=Cube(p0,vec3(0.3));

  return d0;
  //return 1.0;
}

vec3 gn(vec3 p){
  vec2 e=vec2(0.001,0.0);
  return normalize(vec3(
    map(p+e.xyy)-map(p-e.xyy),
    map(p+e.yxy)-map(p-e.yxy),
    map(p+e.yyx)-map(p-e.yyx)
    ));
}

void main(){
  vec3 col=vec3(1.0);

  //vec2 st=(gl_FragCoord.xy*2.0-_resolution.xy)/min(_resolution.x,_resolution.y);
  vec2 st=uv*2.0-1.0;
  st.x*=(_resolution.x/_resolution.y);
  //col=vec3(st,0.0);

  //camera
  vec3 ro=vec3(0.0,0.0,1.0);
  vec3 ta=vec3(0.0);
  vec3 cd=normalize(ta-ro);
  vec3 cs=normalize(cross(cd,vec3(0.0,1.0,0.0)));
  vec3 cu=normalize(cross(cd,cs));
  float dep=1.0;
  vec3 rd=normalize(vec3(cs*st.x+cu*st.y+cd*dep));

  float d,t,acc=0.0;
  int march=0;
  int MAX_MARCH=128;
  for(int i=0;i<128;i++){
    d=map(ro+rd*t);
    march=i;
    if(d<0.001)break;
    t+=d;
    acc+=exp(-3.0*d);
    march=MAX_MARCH-1;
  }

  float glow=0.0;
  const float s = 0.0075;
  vec3 n0=gn(ro+rd*t);
  vec3 n1=gn(ro+rd*t+vec3(sign(n0.x)*s,0.0,0.0));
  vec3 n2=gn(ro+rd*t+vec3(0.0,sign(n0.y)*s,0.0));

  glow=max(0.0,dot(n0,rd));

  float emw=0.8;
  if(dot(n0, n1)<emw || dot(n0, n2)<emw) {
           glow += 4.5;
       }

  glow *= min(1.0,
    4.0-(4.0*float(march) / float(MAX_MARCH-1))
  );

  if(_RenderingTarget==1.0){
     col=vec3(0.2,0.4,0.5)*exp(-.45*t)*glow;
     vec3 refro=ro+rd*t;
     rd=reflect(rd,n0);
     ro=refro;
     t=0.1;
     float acc2=0.0;

     for(int i=0;i<64;i++){
      d=map(ro+rd*t);
      if(d<0.001)break;
      t+=d;
      acc2+=exp(-3.0*d);
    }

    col+=vec3(0.8,0.25,0.8)*exp(-.1*t)*acc2*0.005;

  }else if(_RenderingTarget==2.0){
    col=clamp(1.0-vec3(1.0)*exp(-.45*t),0.0,1.0);
  }

  gl_FragColor=vec4(col,1.0);
}
