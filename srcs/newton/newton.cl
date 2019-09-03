#include "math_complex.h"

static int	check_convergence(t_complex z1, t_complex z2, double margin_error)
{
	t_complex	z;

	z.x = z1.x - z2.x;
	z.y = z1.y - z2.y;
	if (z.x * z.x + z.y * z.y < margin_error)
		return (1);
	return (0);
}

__kernel void newton1(__global int* img, double step_x, double step_y, int depth,
		int width, double left_b, double top_b, double radius, t_complex root1,
		t_complex root2, t_complex root3, int color_mult)
{
	t_complex z;
	int		i = -1;
	int		gid = get_global_id(0);
	int color;

	z.x = left_b + step_x * (gid % width);
	z.y = top_b + step_y * (gid / width);
	while (++i < depth)
	{
		z = cx_minus(z, cx_dev(cx_minus_real(cx_pow(z, 3), 1), cx_mult_real(cx_pow(z, 2), 3)));
		if (check_convergence(z, root1, 0.001))
		{
			color = 1000;
			break;
		}
		if (check_convergence(z, root2, 0.001))
		{
			color = 200000;
			break;
		}
		if (check_convergence(z, root3, 0.001))
		{
			color = 99999999;
			break;
		}
	}
	img[gid] = i * color * color_mult;
}

__kernel void newton2(__global int* img, double step_x, double step_y, int depth,
		int width, double left_b, double top_b, double radius, t_complex root1,
		t_complex root2, t_complex root3, t_complex root4, t_complex root5, int color_mult)
{
	t_complex z;
	int		i = -1;
	int		gid = get_global_id(0);
	int color;

	z.x = left_b + step_x * (gid % width);
	z.y = top_b + step_y * (gid / width);
	while (++i < depth)
	{
		z = cx_minus(z, cx_dev(cx_minus_real(cx_pow(z, 5), 1), cx_mult_real(cx_pow(z, 4), 5)));
		if (check_convergence(z, root1, 0.001))
		{
			color = 100;
			break;
		}
		if (check_convergence(z, root2, 0.001))
		{
			color = 1000;
			break;
		}
		if (check_convergence(z, root3, 0.001))
		{
			color = 10000;
			break;
		}
		if (check_convergence(z, root4, 0.001))
		{
			color = 100000;
			break;
		}
		if (check_convergence(z, root5, 0.001))
		{
			color = 1000000;
			break;
		}
	}
	img[gid] = i * color * color_mult;
}
