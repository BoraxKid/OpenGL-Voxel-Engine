varying float f_color;

void main(void)
{
	int rgb;
	int red;
	int green;
	int blue;
	rgb = (int)f_color;

	red = (rgb >> 16) & 0xFF;
	green = (rgb >> 8) & 0xFF;
	blue = rgb & 0xFF;
	gl_FragColor = vec4(red / 255.0, green / 255.0, blue / 255.0, 1.0);
}
