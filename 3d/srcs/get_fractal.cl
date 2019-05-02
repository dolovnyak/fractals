#include "fractal.h"

kernel void mandelbrot(__global t_fractal_point *point, int z, t_fractal fractal)
{
	int		gid;
	int		i;
	float	comp_x;
	float	comp_y;
	float	comp_z;
	float	rx;
	float	iy;
	float	jz;
	float	tmp;

	gid = get_global_id(0);
	rx = 0.0;
	iy = 0.0;
	jz = 0.0;
	comp_x = fractal.left_b + fractal.step_x * (gid % fractal.x_len);
    comp_y = fractal.top_b + fractal.step_y * (gid / fractal.x_len);
    comp_z = fractal.back_b + fractal.step_z * z;
	i = -1;
	while (++i < fractal.depth && jz * jz + rx * rx + iy * iy < 4)
	{
		tmp = rx * rx - iy * iy - jz * jz + comp_x;
		iy = 2 * rx * iy + comp_y;
		jz = 2 * rx * jz + comp_z;
		rx = tmp;
	}
	point[gid].flag = 0;
	if (i >= fractal.depth)
	{
		point[gid].x = (float)(gid % fractal.x_len - 400);
		point[gid].y = (float)(gid / fractal.x_len - 400);
		point[gid].z = (float)z + 500;
		point[gid].flag = 1;
	}
}
