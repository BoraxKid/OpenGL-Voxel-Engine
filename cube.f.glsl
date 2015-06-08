varying vec3 voxels_color;

void main(void)
{
	gl_FragColor.r = voxels_color.x / 255.0;
	gl_FragColor.g = voxels_color.y / 255.0;
	gl_FragColor.b = voxels_color.z / 255.0;
}
