#include "math_complex.h"

__kernel void burning_ship_2d(__global int* img, double step_x, double step_y, int depth,
		int width, double left_b, double top_b, double radius, int color_mult)
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
	while (++i < depth && real * real + imaginary * imaginary < radius)
	{
		tmp = real * real - imaginary * imaginary;
		imaginary = 2 * fabs(real * imaginary) + comp_y;
		real = tmp + comp_x;
	}
	if (i < depth)
		img[gid] = i * color_mult;
	else
		img[gid] = color_mult / 2;
}

__kernel void burning_ship_2d_pow5(__global int* img, double step_x, double step_y, int depth,
		int width, double left_b, double top_b, double radius, int color_mult)
{
	t_complex	z, z_const;
	int		i = -1;
	int		gid = get_global_id(0);

	z_const.x = left_b + step_x * (gid % width);
	z_const.y = top_b + step_y * (gid / width);
	z.x = 0.0;
	z.y = 0.0;
	while (++i < depth && z.x * z.x + z.y * z.y < radius)
	{
		z.x = fabs(z.x);
		z.y = fabs(z.y);
		z = cx_plus(cx_pow(z, 5), z_const);
	}
	if (i < depth)
		img[gid] = i * color_mult;
	else
		img[gid] = color_mult / 2;
}
