#version 330

in vec2 uv;
in float iTime;

out vec4 outColor;

#define PI 3.14159265
#define rot(a) mat2(cos(a),sin(a),-sin(a),cos(a))

vec2 pmod(vec2 p,float n)
{
    float a=(2.0*PI)/n;
    float t=atan(p.x,p.y)-PI/n;
    t=mod(t,a)-PI/n;
    return vec2(length(p)*cos(t),length(p)*sin(t));
}

float Cube(vec3 p,float s)
{
    p=abs(p);
    return length(max(p-vec3(s),0.0));
}

float ft(vec3 p,vec3 offset,float scale)
{
    vec4 z=vec4(p.xyz,1.0);
    int count=10;
    
    for(int i;i<count;i++)
    {
        if(z.x+z.y<0.0)z.xy=-z.yx;
        if(z.x+z.z<0.0)z.xz=-z.zx;
        if(z.y+z.z<0.0)z.yz=-z.yz;
        z*=scale;
        z.xyz-=offset*(scale-1.0);
    }
    return Cube(z.xyz,1.0)/z.w;
    //return (length(z.xyz)-1.5)/z.w;
}

float cube(vec3 p,vec3 s)
{
    p=abs(p);
    return length(max(p-s,0.0));
}

float sdcross(vec3 p,float s)
{
    p=abs(p);
    float dxy=max(p.x,p.y);
    float dxz=max(p.x,p.z);
    float dyz=max(p.y,p.z);
    return min(dxy,min(dxz,dyz))-s;
}

float menger(vec3 pos)
{
    //pos*=3.;
    float th=0.125;
     float d=cube(pos,vec3(0.95)*th*2.);
    
        //!!!!!!!!!!!!!!  1.0-4.0
        float s=1.1;

        //!!!!!!!!!!!!!!!! 1.0-2.0
        float scale=1.4;

        for(int h=0;h<3;h++)
        {
            //!!!!!!!!!1.0-2.0
            float k=1.75;
            pos=mod(pos*s,k)-k*0.5;
            //pos.xz=pf(p.xz,4.0);
            pos=1.0-scale*abs(pos);
            s*=scale;
             //!!!!!!!!!!!!!!!!! 0.5-1.0
            d=max(d,sdcross(pos,
            .85*th*1.25)/s);  

        }

        return d;
}


float map(vec3 p,inout float acc2)
{

    vec3 pos=p;
    pos.xy*=rot(iTime*0.5);
    pos.xz*=rot(iTime*0.5);
    pos.yz*=rot(iTime*0.5);
    //float d1=menger(pos);
    float time=iTime*2.;
    float r=floor(time)+pow(fract(time),.3);
   float d1=100.0;
   if(cube(pos,vec3(0.03))<0.8){
        for(int h=0;h<3;h++){
        pos=abs(pos)-.05;
        pos.xy*=rot(r);
        pos.xz*=rot(r);
        pos.yz*=rot(r);
         pos.x-=sin(r)*0.1;
        }
    d1=cube(pos,vec3(0.03));
    acc2+=exp(-3.0*d1);
   }
 
    for(int q=0;q<2;q++)
    {
        p=abs(p)-vec3(.5,.2,.67);
        float a=1.5;
        p.xy*=rot(a);
        p.xz*=rot(a);
        p.yz*=rot(a);
        
       
        
    }
    
    float s=.85;
    p=abs(p)-1.0*s;
    p=abs(p)-6.0*s;
    p=abs(p)-2.0*s;
    p=abs(p)-3.0*s;
    
    float k=3.0;
    p.y=mod(p.y,k)-k*0.5;

    ///////////////////////////////////
    float d2= ft(p,vec3(1.4),1.8);
  
    return min(d1,d2);
    //return d2;
}


void main(){
 vec2 st=uv*2.0-1.0;
       
    vec3 col=vec3(0.);
    
     float radius=10.;
   float speed=-.25;
    vec3 ta=vec3(0.);
    vec3 ro=vec3(cos(iTime*speed)*radius,sin(iTime*0.5)*0.25,sin(iTime*speed)*radius);
    
    vec3 cDir=normalize(ta-ro);
    vec3 cSide=cross(cDir,vec3(0.,-1.,0.));
    vec3 cUp=cross(cDir,cSide);
    float depth=1.;
    vec3 rd=vec3(st.x*cSide+st.y*cUp+cDir*depth);
    
    
    float d,t,acc,acc2,flash=0.0;
    
    for(int i=0;i<80;i++)
    {
        d=map(ro+rd*t,acc2);
        if(d<0.004||t>10.0)break;
        t+=d*0.5;
        acc+=exp(-1.0*d);
        if(mod(distance(vec3(0.0),ro+rd*t)-iTime*10.0,10.0)<1.0)
        {
            flash+=exp(-3.0*d);
        }
    }
    
    //col=vec3(exp(-.45*t));
    col=vec3(0.,.8,.75)*acc*0.015;
     col+=vec3(1.,1.,1.)*acc2*0.03;
     col+=vec3(0.,.75,1.)*flash*0.02;

	outColor=vec4(col,1.0);
}