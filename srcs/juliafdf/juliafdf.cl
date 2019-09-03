static void get_rotation_and_draw_julia(int gid, int width, int height, int z, double angle_x,
		double angle_z, int  center_x, int center_y, int zoom, __global int *img, int color_mult)
{
	int x, y, tmp_x;

	x = zoom * (gid % width - width / 2);
	y = zoom * (gid / width - height / 2);
	tmp_x = center_x + x * cos(angle_z) - y * sin(angle_z);
	y = y * cos(angle_z) + x * sin(angle_z);
	y = center_y - y * cos(angle_x) - z * sin(angle_x);
	x = tmp_x;
	if (x >= 0 && x < width && y >= 0 && y < height)
		img[x + width * y] = z * color_mult;
}

__kernel void julia_fdf(__global int* img, double step_x, double step_y, int depth,
		int width, int height, int center_x, int center_y, int zoom, double left_b,
		double top_b, double const_real, double const_imagin, double angle_x,
		double angle_z, double radius, int color_mult)
{
	double	comp_x, comp_y;
	double	tmp;
	double	real, imaginary;
	int		i = -1;
	int		gid = get_global_id(0);

	comp_x = left_b + step_x * (gid % width);
	comp_y = top_b + step_y * (gid / width);
	real = comp_x;
	imaginary = comp_y;
	while (++i < depth && real * real + imaginary * imaginary < radius)
	{
		tmp = real * real - imaginary * imaginary;
		imaginary = 2 * real * imaginary + const_imagin;
		real = tmp + const_real;
	}
	if (i < depth)
		get_rotation_and_draw_julia(gid, width, height, i, angle_x, angle_z,
				center_x, center_y, zoom, img, color_mult);
	else
		get_rotation_and_draw_julia(gid, width, height, i, angle_x, angle_z,
				center_x, center_y, zoom, img, color_mult / 10);
}
