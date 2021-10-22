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

vec2 pmod(vec2 p, float n)
{
float a = (2.0 * PI) / n;
float t = atan(p.x, p.y) - PI / n;
t = mod(t, a) - PI / n;
return vec2(length(p) * cos(t), length(p) * sin(t));
}

float cube(vec3 p, vec3 s)
{
p = abs(p);
return length(max(p - s, 0.0));
}

float sdHexPrism(vec3 p, vec2 h)
{
const vec3 k = vec3(-0.8660254, 0.5, 0.57735);
p = abs(p);
p.xy -= 2.0 * min(dot(k.xy, p.xy), 0.0) * k.xy;
vec2 d = vec2(
    length(p.xy - vec2(clamp(p.x, -k.z * h.x, k.z * h.x), h.x)) * sign(p.y - h.x),
    p.z - h.y);
return min(max(d.x, d.y), 0.0) + length(max(d, 0.0));
}

#define rootT 1.73205080757


float hex(vec3 p) {
    p.yz *=rot(PI / 2.0); 

    float r = 5.;
    float l = 5.;
    p.xy = abs(p.xy);
    float offset = 0.5;

    vec3 pos1 = p;
    vec3 pos2 = p;
    vec2 off1 = vec2(2.0, 2.0 * rootT) * r+vec2(offset, offset);

    vec2 id1 = floor(pos1.xy / off1);
    vec2 id2 = floor((pos1.xy+0.5* off1) / off1);

    float str = 1.5;
    float randZ1 = rand(id1)* str;
    float randZ2 = rand(id2)* str;


    pos1.xy = mod(pos1.xy, off1) - off1 * 0.5;
    pos2.xy = mod(pos2.xy + 0.5 * off1, off1) - off1 * 0.5;

    pos1.z += randZ1;
    pos2.z += randZ2;

    float d1 = sdHexPrism(pos1, vec2(r, l));
    float d2 = sdHexPrism(pos2, vec2(r, l));




    d1 = min(d1, d2);

    return d1;
}

float Torus(vec3 p,vec2 size)
{
    return length(vec2(length(p.xy)-size.x,p.z))-size.y;
}

float Box(vec3 p,vec3 size)
{
    return length(max(abs(p)-size,0.0));
}

float flower(vec3 p)
{
    p.xy*=rot(iTime);
    p.xz*=rot(iTime);
    p.yz*=rot(iTime);
    
    float radius=1.0;
    
    vec3 pos=p;
        float time=iTime*2.;
    float r=floor(time)+pow(fract(time),.1);
   
    
    for(int i=0;i<3;i++)
    {
        pos=abs(pos)-radius;
        if(pos.x<pos.y)pos.xy=pos.yx;
        if(pos.x<pos.z)pos.xz=pos.zx;
        if(pos.y<pos.z)pos.yz=pos.zy;
        pos.xy-=.01;
        
        pos.xy*=rot(r);
        pos.xz*=rot(r);
        pos.y-=0.5;
        
        //pos.yz*=rot(PI/3.);
    }
    
    float h=2.0;
    pos.x-=clamp(pos.x,-h,h);
    
    float d4=Torus(pos,vec2(0.5,0.35));
    float d5=Box(pos,vec3(0.1,0.1,4.0));
    return d4;
}

float map(vec3 p)
{
    vec3 pos=p;
    
    p.z -= iTime*20.;
    float off = 16.;

    float d1 = hex(p- vec3(0.0, off, 0.0));
    float d2 = hex(p+vec3(0.0, off,0.0));

    float d3=flower(pos);
    //return d1;
    return min(min(d1,d2),d3);
}


vec3 gn(vec3 p) {
    vec2 e = vec2(0.001, 0.0);
    return normalize(vec3(
        map(p+e.xyy)-map(p-e.xyy),
        map(p + e.yxy) - map(p - e.yxy),
        map(p + e.yyx) - map(p - e.yyx)
        ));
}

void main(){
        vec2 st=uv*2.0-1.0;

        vec3 col=vec3(0.);

         float radius=15.;
       float speed=-.25;
        vec3 ta=vec3(0.);
        vec3 ro=vec3(cos(iTime*speed)*radius,0.0,sin(iTime*speed)*radius);
        //sin(iTime*0.5)*0.25
        //vec3 ro=vec3(0.,0.,15.0);
        vec3 cDir=normalize(ta-ro);
        vec3 cSide=cross(cDir,vec3(0.,-1.,0.));
        vec3 cUp=cross(cDir,cSide);
        float depth=1.;
        vec3 rd=vec3(st.x*cSide+st.y*cUp+cDir*depth);

        float d, t, acc, flash = 0.0;
        float adjD = 1.;

        for (int i = 0; i < 80; i++)
        {
            d = map(ro + rd * t);
            if (d < 0.001 )break;
            t += d * adjD;
            acc += exp(-1.0 * d);


        }

        vec3 refRo = ro + rd * t;
        vec3 n = gn(refRo);
        rd = reflect(rd, n);
        //rd = refract(rd, n,0.5);
        ro = refRo;
        t = 0.1;
        float acc2 = 0.0;
        for (int i = 0; i < 40; i++) {
            d = map(ro + rd * t);
            if (d < 0.001)break;
            t += d* adjD;
            acc2 += exp(-1.0 * d);
        }


        col = acc* vec3(1.0,1.,1.) *0.02;
        col += acc2 * vec3(1.,1.,1.) * 0.02;

	outColor=vec4(col,1.0);
}