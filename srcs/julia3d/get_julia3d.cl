#include "fractal3d.h"

kernel void julia_3d(__global t_fractal_point *point, int z, t_fractal3d fractal)
{
	int		gid;
	int		i;
	float	rx;
	float	iy;
	float	jz;
	float	tmp;

	gid = get_global_id(0);
	rx = fractal.left_b + fractal.step_x * (gid % fractal.x_len);
    iy = fractal.top_b + fractal.step_y * (gid / fractal.x_len);
    jz = fractal.back_b + fractal.step_z * z;
	i = -1;
	while (++i < fractal.depth && jz * jz + rx * rx + iy * iy < 4)
	{
		tmp = rx * rx - iy * iy - jz * jz + fractal.const_x;
		iy = 2 * rx * iy + fractal.const_iy;
		jz = 2 * rx * jz + fractal.const_jz;
		rx = tmp;
	}
	point[gid].flag = 0;
	if (i >= 100)
	{
		point[gid].x = (float)(gid % fractal.x_len - fractal.x_len / 2);
		point[gid].y = (float)(gid / fractal.x_len - fractal.y_len / 2);
		point[gid].z = (float)z + 60;
		point[gid].r = i % 255;
		point[gid].g = 0;
		point[gid].b = i % 100;
		point[gid].flag = 1;
	}
}
