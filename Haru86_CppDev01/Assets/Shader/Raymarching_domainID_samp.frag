#version 330

in vec2 uv;
in float iTime;

out vec4 outColor;

#define PI 3.14159265

float rand(vec2 st)
{
    return fract(sin(dot(st, vec2(12.9898, 78.233))) * 43758.5453);
}

 float PerlinNoise(float x) {
                float aL = rand(vec2(floor(x), 0.1));
                float aR = rand(vec2(floor(x + 1.0), 0.1));
                float wL = aL * fract(x);
                float wR = aR * (fract(x) - 1.0);
                float f = fract(x);
                float u = pow(f, 2.0) * (3.0 - 2.0 * f);
                float n = mix(wL, wR, u);

                return n;
            }

float Box(vec3 p,vec3 size)
{
    return length(max(vec3(0.0),abs(p)-size));
}

float map(vec3 p,inout vec3 col)
{
    p.z-=iTime;

    vec3 pos=p;
    float modNum=0.75;
    //get axis random id
    float xid=floor(pos.x/modNum);
    float yid=floor(pos.y/modNum);
    float zid=floor(pos.z/modNum);
    
    pos.xz=mod(pos.xz,modNum)-0.5*modNum;

   
    
    return Box(pos,vec3(0.2,
    0.0 
    ,0.2))-0.15;

    //aud*2.0
    
}

void main(){
        vec2 st=uv*2.0-1.0;

    vec3 col = vec3(0,0,0);
 
    vec3 ro=vec3(0.0,-8.0,6.0);
    vec3 target=vec3(0,0,0);
    vec3 cDir=normalize(target-ro);
    vec3 cSide=cross(cDir,vec3(0.0,1.0,0.0));
    vec3 cUp=cross(cDir,cSide);
    float depth=1.0;
    vec3 rd=vec3(st.x*cSide+st.y*cUp+depth*cDir);
    
       vec3 mapCol = vec3(0);
    float d, t = 0.;
    for(int i=0;i<128;i++)
    {
        d = map(ro + rd*t, mapCol);
        if(d<0.001||t>100.0)break;
        t+=d*.35;
    }
    
   
    vec3 p = ro + rd*t;
    // Directional derivative lighting.   
    float dif = max((map(p - .01, mapCol) - map(p, mapCol))/.01, 0.);
    col = vec3(exp(-0.05*t))*mapCol*(dif + .2)*2.;

	outColor=vec4(col,1.0);
}