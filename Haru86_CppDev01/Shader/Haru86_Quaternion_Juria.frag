#version 330

in vec2 uv;
in float iTime;

out vec4 outColor;

#define PI 3.14159265
#define rot(a) mat2(cos(a),sin(a),-sin(a),cos(a))

float rand(vec2 st)
{
    return fract(sin(dot(st, vec2(12.9898, 78.233))) * 43758.5453);
}


vec4 qmul(vec4 a, vec4 b) {
    return vec4(
        a.x * b.x - a.y * b.y - a.z * b.z - a.w * b.w,
        a.x * b.y + a.y * b.x - a.z * b.w + a.w * b.z,
        a.x * b.z + a.y * b.w + a.z * b.x - a.w * b.y,
        a.x * b.w - a.y * b.z + a.z * b.y + a.w * b.x
    );
}

vec2 pmod(vec2 p,float n)
{
    float a=(2.0*PI)/n;
    float t=atan(p.x,p.y)-PI/n;
    t=mod(t,a)-PI/n;
    return vec2(0.75*length(p)*cos(t),0.75*length(p)*sin(t));
}


#define ITERATIONS 16
float deQuaternionJuliaSet(vec4 p, vec4 c) {
    vec4 z = p;
    vec4 dz = vec4(1.0, 0.0, 0.0, 0.0);
    vec4 pz, pdz;
    float r = 0.0, dr = 1.0;
    for (int i = 0; i < ITERATIONS; i++) {
        pz = z;
        z = qmul(pz, pz) + c;
        pdz = dz;
        dz = 2.0 * qmul(pz, pdz);
        r = length(z);
        dr = length(dz);
        if (r > 4.0) break;
    }
    return 0.5 * log(r) * r / dr;
}

float de(vec3 p) {
    return deQuaternionJuliaSet(vec4(p, 0.0), vec4(-1.0, 0.2, 0.0, 0.0));
}

float Cube(vec3 p,vec3 s)
{
    p=abs(p);
    return length(max(p-s,0.0));
}

float sdCross(vec3 p,float s)
{
    p=abs(p);
    float dxy=max(p.x,p.y);
    float dyz=max(p.y,p.z);
    float dzx=max(p.z,p.x);
    return min(dxy,min(dyz,dzx))-s;
}

float menger(vec3 pos)
{
    float d=Cube(pos,vec3(0.95));
    
        //!!!!!!!!!!!!!!  1.0-4.0
            float s=3.;

        //!!!!!!!!!!!!!!!! 1.0-2.0
        float scale=1.0;

        for(int h=0;h<3;h++)
        {
            //!!!!!!!!!1.0-2.0
            float k=2.; 

            pos=mod(pos*s,k)-k*0.5;
            //pos.xz=pf(p.xz,4.0);
            pos=1.0-scale*abs(pos);
            s*=scale;
             //!!!!!!!!!!!!!!!!! 0.5-1.0
            d=max(d,sdCross(pos,
            .7)/s);  

        }

    return d;
}


float map(vec3 p)
{
    
    vec3 pos=p;
    float d=length(pos)-0.45;
    d=1000.0;
    pos.xy*=rot(PI/2.0);
    float j=2.0;
    pos.x=mod(pos.x,j)-j*0.5;
    pos.x=abs(pos.x);
    float d1=de(pos);
    
    
    ////////////////////////////////////////////
   
   vec3 pos2=p;
   pos2.xy*=rot(PI/2.0);
 
    for(int i=0;i<6;i++)
    {
         float cvalue=1.5;
       vec3 c=vec3(
            (rand(vec2(float(i),0.321)))*cvalue,
            (rand(vec2(float(i),0.654)))*cvalue,
            (rand(vec2(float(i),0.987)))*cvalue
        );
       pos2.z=abs(pos2.z)-c.x;
       pos2=abs(pos2)-c.y;
       
       
        vec3 b=vec3(
            (rand(vec2(float(i),0.321)))*4.0*PI-2.0*PI,
            (rand(vec2(float(i),0.654)))*4.0*PI-2.0*PI,
            (rand(vec2(float(i),0.987)))*4.0*PI-2.0*PI
        );
        pos2.xy*=rot(b.x);
        pos2.xz*=rot(b.y);
        pos2.yz*=rot(b.z);
        
      
        
    }
      pos2.z=abs(pos2.z)-1.;
    float s=0.2;
    pos2=abs(pos2)-10.0*s;
    pos2=abs(pos2)-2.0*s;
    pos2=abs(pos2)-3.0*s;
    pos2=abs(pos2)-6.0*s;
   
    float d2=menger(pos2);

   return min(d1,d2);
}

void main(){
        vec2 st=uv*2.0-1.0;

    vec3 col=vec3(0.0);
    
    
   
   float radius=.9;
   float speed=-.25;
    vec3 ta=vec3(0.);
    vec3 ro=vec3(cos(iTime*speed)*radius,sin(iTime*0.5)*0.25,sin(iTime*speed)*radius);
    
    vec3 cDir=normalize(ta-ro);
    vec3 cSide=cross(cDir,vec3(0.,-1.,0.));
    vec3 cUp=cross(cDir,cSide);
    float depth=1.;
    vec3 rd=vec3(st.x*cSide+st.y*cUp+cDir*depth);
    
    float d,t,acc=0.0;
    for(int i=0;i<128;i++)
    {
        d=map(ro+rd*t);
        if(d<0.001||t>100.0)break;
        t+=d*0.75;
        acc+=exp(-3.0*d);
    }
    
    //vec3(exp(-2.5*t))+
    col=vec3(1.,0.5,0.5)*acc*0.03;
    col+=vec3(1.,.5,0.5)*acc*exp(-6.*t);

	outColor=vec4(col,1.0);
}