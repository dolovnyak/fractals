__kernel void mandelbrot(__global int* img, double step_x, double step_y, int depth,
		int width, double left_b, double top_b, color_mult)
{
	double	comp_x, comp_y;
	double	tmp;
	double	real, imaginary;
	int		i = -1;
	int		gid = get_global_id(0);

	comp_x = left_b + step_x * (gid % width);
	comp_y = top_b + step_y * (gid / width);
	real = 0.0;
	imaginary = 0.0;
	while (++i < depth && real * real + imaginary * imaginary < 4)
	{
		tmp = real * real - imaginary * imaginary;
		imaginary = 2 * real * imaginary + comp_y;
		real = tmp + comp_x;
	}
	if (i < depth)
		img[gid] = i * 2000000;
	else
		img[gid] = 1000000;
}
