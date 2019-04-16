typedef struct	s_sphera
{
	float	x;
	float	y;
	float	z;
	float	radius;
	int		r;
	int		g;
	int		b;
	int		flag;
}				t_sphera;

kernel void check_struct(__global t_sphera* spheres)
{
	int	gid = get_global_id(0);

	spheres[gid].radius = (float)gid;
	printf ("program work");
	printf ("%d\n", gid);
}
