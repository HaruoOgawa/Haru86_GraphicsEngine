#version 410 
layout(triangles) in;
layout(triangle_strip,max_vertices=3) out;
//layout(line_strip,max_vertices=4) out;

uniform mat4 MVPMatrix;
uniform mat4 MMatrix;
uniform mat4 VMatrix;
uniform mat4 PMatrix;
uniform float _time;
uniform float _deltaTime;

out vec3 g2f_normal;

void main(){
    vec4 p0=gl_in[0].gl_Position;
    vec4 p1=gl_in[1].gl_Position;
    vec4 p2=gl_in[2].gl_Position;

    vec3 normal=normalize(cross(normalize(p1.xyz-p0.xyz),normalize(p2.xyz-p0.xyz)));

    gl_Position =p0;
    g2f_normal=(MMatrix*vec4(normal,1.0)).xyz;
    EmitVertex();

    gl_Position =p1;
    g2f_normal=(MMatrix*vec4(normal,1.0)).xyz;
    EmitVertex();
    
    gl_Position =p2;
    g2f_normal=(MMatrix*vec4(normal,1.0)).xyz;
    EmitVertex();
    
    EndPrimitive();
}