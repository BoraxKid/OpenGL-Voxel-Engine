attribute vec3 coord;
attribute vec3 colors;
uniform mat4 mvp;
varying vec3 voxels_color;

void main(void)
{
	gl_Position = mvp * vec4(coord.xzy, 1.0);
	voxels_color = colors;
}
