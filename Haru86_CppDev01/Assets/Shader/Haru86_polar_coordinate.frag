#version 330

in vec2 uv;
in float iTime;

out vec4 outColor;

#define time iTime
float PI = 3.1415926535;
float bpm = 108.0;


mat2 rot(float r){
  return mat2(cos(r),sin(r),-sin(r),cos(r));
}

float cube(vec3 p, vec3 s){
  vec3 q = abs(p);
  vec3 m = max(s-q,0.0);
  return length(max(q-s,0.0))-min(min(m.x,m.y),m.z);
}

float Sphere(vec3 p,float s)
{
    return length(p)-s;
}

float map(vec3 p){
  
  float ad=1.0;
  float a=atan(p.x,p.z);
  float l=log(length(p.xz));
  
  
  
  //pos1
  vec3 pos1=p;
  pos1.xz=vec2(l,a-iTime);
  pos1.xz*=5.0;
  pos1.x+=iTime*2.0;
  //pos1.y+=max(l*3.0,0.0);
  pos1.y+=sin(3.0*iTime+l*10.0)*l;
  //pos1.y=max(pos1.y,0.0);
  
  //pos2
  vec3 pos2=p;
  pos2.xz=vec2(l,a-iTime*2.0);
  pos2.xz*=5.0;
   //pos2.y+=l*3.0;
  pos2.y+=max(l*3.0,0.0);
  pos2.x+=2.0*iTime;
  
  
  float k = 0.75;
  pos1.xz= mod(pos1.xz,k)-0.5*k;
  float k2=5.0;
  pos2.xz=mod(pos2.xz,k2)-k2*0.5;
 
  float d = cube(pos1,float(1.0)*vec3(0.5,0.5,0.5)*0.5);
  float d2=Sphere(pos2+vec3(0.0,0.5,0.0),0.5);
  
  
  return d;
 // return min(d,d2);
}

vec3 gn(vec3 p)
{
    vec2 e=vec2(0.001,0.0);
    return normalize(vec3(map(p+e.xyy)-map(p-e.xyy),
                map(p+e.yxy)-map(p-e.yxy),
                map(p+e.yyx)-map(p-e.yyx)));
}



void main(){
        vec2 st=uv*2.0-1.0;

        vec3 col=vec3(0.);
    
    vec3 ro=vec3(0.0,-24.0-sin(iTime)*8.0,16.0);
    vec3 ta=vec3(0.0,0.0,0.0);
    //vec3 ro=vec3(cos(iTime*0.5)*10.0,-8.0,10.0*sin(iTime*0.5));
    
    vec3 cDir=normalize(ta-ro);
    vec3 cSide=(cross(cDir,vec3(0.0,1.0,0.0)));
    vec3 cUp=(cross(cDir,cSide));
    float depth=2.0;
    vec3 rd=normalize(vec3(st.x*cSide+st.y*cUp+depth*cDir));
    
    float d,t=0.0;
    float tsr;
    vec3 ac = vec3(0.0);

    float ad=1.0;
    for(int i = 0;i<66;i++){
      d = map(ro+rd*t);
     
      t += d*0.5;
      ac += exp(-d*12.);
      if(d<0.0001||t>1000.0)break;
    }
    
    vec3 sd=ro+rd*t;
    vec3 normal=gn(sd);
    ro=sd;
    rd=reflect(rd,normal);
    t=0.1;
    float acc2=0.0;
    
    for(int i=0;i<33;i++)
    {
         d=map(ro+rd*t);
         if(d<0.001)break;
         t+=d*0.5;
         acc2+=exp(-3.0*d);
    }
    
  

    col = 0.06*ac*vec3(0.2,1.0,1.0);
    col+=0.03*acc2*vec3(0.0,0.0,1.0);

	outColor=vec4(col,1.0);
}