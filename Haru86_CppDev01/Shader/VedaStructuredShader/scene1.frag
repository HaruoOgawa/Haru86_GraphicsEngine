precision mediump float;
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

#define rot(a) mat2(cos(a),sin(a),-sin(a),cos(a))

float map(vec3 p){
  return length(p)-0.5;
}

vec3 gn(vec3 p){
  vec2 e=vec2(0.001,0.);
  return normalize(
    vec3(
      map(p+e.xyy)-map(p-e.xyy),
      map(p+e.yxy)-map(p-e.yxy),
      map(p+e.yyx)-map(p-e.yyx)
      )
    );
}

void main(void) {
  vec2 st = (gl_FragCoord.xy*2.0-resolution.xy) / min(resolution.x,resolution.y);
  vec3 col=vec3(0.,0.,0.);
  vec3 ro=vec3(0.,0.,1.0);
  vec3 rd=vec3(st,-1.0);

  float d,t,acc=0.0;
  for(int i=0;i<64;i++){
    d=map(ro+rd*t);
    if(d<0.001)break;
    t+=d;
    acc+=exp(-3.0*d);
  }

  vec3 n=gn(ro+rd*t);

  col=vec3(exp(-1.0*t))*vec3(0.,0.,1.);

  gl_FragColor = vec4(n, 1.0);
}
