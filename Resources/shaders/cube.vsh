attribute vec3 aPos;
attribute vec2 aTx;
attribute vec3 aNorm;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 rot;

varying vec2 Tx;
varying vec3 Norm; 
varying vec4 frag_pos;

void main()
{
	gl_Position = projection*view*model*vec4(aPos.x , aPos.y , aPos.z, 1.0);
	Tx=aTx;
	Norm=vec3(rot*vec4(aNorm,1.0));
	frag_pos=model*vec4(aPos,1.0);
}