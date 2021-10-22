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

float sdCross(vec3 p)
{
    p=abs(p);
    float dxy=max(p.x,p.y);
    float dyz=max(p.y,p.z);
    float dzx=max(p.z,p.x);
    return min(dxy,min(dyz,dzx))-1.0;
}


float map(vec3 p)
{
    p.z+=iTime;
    
    //IFS
    p.xy=pmod(p.xy,6.0);
    float k=4.;
    p=mod(p,k)-0.5*k;
   
    
    //Modeling
    float s=2.0;
    float d=Cube(p,s);
    float scale=6.0;
    for(int i=0;i<6;i++)
    {
        p=mod(p,2.0)-1.0;
        s*=scale;
        p=1.0-scale*abs(p);
        d=max(d,sdCross(p)/s);
    }
    
    
   

    return d;
}

void main(){
        vec2 st=uv*2.0-1.0;

    vec3 col=vec3(0.);
    
    vec3 ta=vec3(0.0);
   // vec3 ro=vec3(cos(iTime)*0.5,0.0,sin(iTime)*0.5);
    vec3 ro=vec3(0.25,.25,1.0);
    vec3 cDir=normalize(ta-ro);
    vec3 cSide=cross(cDir,vec3(0.0,1.0,0.0));
    vec3 cUp=cross(cDir,cSide);
    float depth=1.0;
    vec3 rd=vec3(st.x*cSide+st.y*cUp+depth*cDir);
    
    //vec3 rd=vec3(st.xy,1.0);
    
    
    float d,t,acc=0.0;
    
    for(int i=0;i<64;i++)
    {
        d=map(ro+rd*t);
        if(d<0.0001)break;
        t+=d;
        acc+=exp(d);
    }
    
    col=vec3(exp(-0.5*t));
    col*=vec3(1.,0.,0.)*acc*0.04;

	outColor=vec4(col,1.0);
}