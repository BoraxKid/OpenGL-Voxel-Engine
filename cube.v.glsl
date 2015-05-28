attribute vec4 coord;
uniform mat4 mvp;
varying float f_color;

void main(void)
{
	gl_Position = mvp * vec4(coord.xyz, 1.0);
	f_color = coord.w;
}
