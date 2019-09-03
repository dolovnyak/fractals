#include "math_complex.h"

__kernel void julia_2d(__global int* img, double step_x, double step_y, int depth,
		int s_width, double left_b, double top_b, double const_real, double const_imagin,
		double radius, int color_mult)
{
	double	tmp;
	double	real, imaginary;
	int		i = -1;
	int		gid = get_global_id(0);

	real = left_b + step_x * (gid % s_width);
	imaginary = top_b + step_y * (gid / s_width);
	while (++i < depth && real * real + imaginary * imaginary < radius)
	{
		tmp = real * real - imaginary * imaginary;
		imaginary = 2 * real * imaginary + const_imagin;
		real = tmp + const_real;
	}
	if (i < depth)
		img[gid] = i * color_mult;
	else
		img[gid] = color_mult / 2;
}

__kernel void julia_2d_pow5(__global int* img, double step_x, double step_y, int depth,
		int s_width, double left_b, double top_b, double const_real, double const_imagin,
		double radius, int color_mult)
{
	t_complex	z_const, z;
	int		i = -1;
	int		gid = get_global_id(0);

	z_const.x = const_real;
	z_const.y = const_imagin;
	z.x = left_b + step_x * (gid % s_width);
	z.y = top_b + step_y * (gid / s_width);
	while (++i < depth && z.x * z.x + z.y * z.y < radius)
		z = cx_plus(cx_pow(z, 5), z_const);
	if (i < depth)
		img[gid] = i * color_mult;
	else
		img[gid] = color_mult / 2;
}
