void	get_rotation_and_draw(int gid, int width, int height, int z, double angle_x,
			double angle_z, int  center_x, int center_y, int zoom, __global int *img)
{
	float x, y, tmp_x;

	x = zoom * (gid % width - width / 2);
	y = zoom * (gid / width - height / 2);
	tmp_x = center_x + x * cos(angle_z) - y * sin(angle_z);
	y = y * cos(angle_z) + x * sin(angle_z);
	y = center_y - y * cos(angle_x) - z * sin(angle_x);
	x = tmp_x;
	if ((int)x >= 0 && (int)x < width && (int)y >= 0 && (int)y < height)
		img[(int)x + width * (int)y] = 1200000;
}

__kernel void mandelbrot3d(__global int* img, double step_x, double step_y, int depth,
	int width, int height, int center_x, int center_y, int zoom,
	double left_b, double top_b, double angle_x, double angle_z)
{
    double  comp_x, comp_y;
    double  tmp;
    double  real, imaginary;
    int     i = -1;
    int     gid = get_global_id(0);

    comp_x = left_b + step_x * (gid % width);
    comp_y = top_b + step_y * (gid / width);
    real = 0.0;
    imaginary = 0.0;
    while (++i < depth && sqrt(real * real + imaginary * imaginary) < 2)
    {
        tmp = real * real - imaginary * imaginary;
        imaginary = 2 * real * imaginary + comp_y;
        real = tmp + comp_x;
    }
	if (i < depth)
		get_rotation_and_draw(gid, width, height, i, angle_x, angle_z,
			   center_x, center_y, zoom, img);
}
