#version 330

uniform vec3 _CameraPosition;
uniform vec3 _lightDir;

in vec3 worldPosition;
in vec3 worldNormal;

void main(){
	vec3 col=vec3(1.0);

	//diffuse
	vec3 L=normalize(_lightDir);
	float diff=max(0.0,dot(worldNormal,L));
	col.rgb*=diff;

    //Specular
    vec3 viewDir=normalize(_CameraPosition- worldPosition);
    vec3 H=normalize(viewDir+_lightDir);
    float spec=pow(max(0.0,dot(H,worldNormal)),2.0);
   //col.rgb*=spec;

  col+=0.01;

  //col=(worldNormal+1.0)*0.5;

	gl_FragColor=vec4(col,0.5);
}