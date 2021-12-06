#version 430

struct g2f{
	vec4 vertex ;
	vec2 uv ;
	float node_life;
	float trail_ID ;
	vec4 trail_color;
};

in float g2f_flag;
in g2f g2f_o;

uniform float _time;
uniform float _initNodeLife;

#define LightDir vec3(-0.613121, -0.1916, 0.766402)

void main(){
	vec4 col=vec4(1.0);
	col.rgb=vec3(0.0);

	float flag=g2f_flag;
	if(flag==0.0){
		//discard;
	}

	float node_life=1.0-clamp(_time-g2f_o.node_life,0.0,_initNodeLife)/_initNodeLife;
    //col.a=node_life; 

	gl_FragColor=col;
}
