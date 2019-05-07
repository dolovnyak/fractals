#include "check_struct.h"

kernel void check_struct(__global t_sphera* spheres)
{
	int	gid = get_global_id(0);

	spheres[gid].radius = (float)gid;
	ft_printf(gid);
//	printf ("%d\n", gid);
}
