typedef struct	s_sphera
{
	float	x;
	float	y;
	float	z;
	int		r;
	int		g;
	int		b;
	int		flag;
}				t_sphera;

kernel void mandelbrot(__global t_sphera* sphera, int sphere_z, float step_x,
		float step_y, float step_z, int depth, int x_len, int y_len, int z_len,
		float left_b, float top_b, float back_b)
{
	int	gid = get_global_id(0);
	int i;
	float  comp_x;
	float  comp_y;
	float  comp_z;
	float  rx;
	float  iy;
	float  jz;
	float  tmp;

	rx = 0.0;
	iy = 0.0;
	jz = 0.0;
	comp_x = left_b + step_x * (gid % x_len);
    comp_y = top_b + step_y * (gid / x_len);
    comp_z = back_b + step_z * (step_x);
	i = -1;
	while (++i < depth && jz * jz + rx * rx + iy * iy < 4)
	{
		tmp = rx * rx - iy * iy - jz * jz + comp_x;
		iy = 2 * rx * iy + comp_y;
		jz = 2 * rx * jz + comp_z;
		rx = tmp;
	}
	sphera[gid].flag = 0;
	if (i >= depth)
	{
		sphera[gid].x = (float)(gid % x_len - 400);
		sphera[gid].y = (float)(gid / x_len - 400);
		sphera[gid].z = (float)sphere_z - 400;
		sphera[gid].flag = 1;
//		printf ("OK\n");
	}
//	printf ("program work\n");
}
