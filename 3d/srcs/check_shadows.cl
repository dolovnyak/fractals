#include "config_cl.h"

int		get_intersect_shadows(t_object3d *obj, t_vector3d intersect_point,
		t_vector3d direction, float *intersect_dist, float min_distance)
{
	if (obj->light_source == 0)
	{
		if (obj->type == 1)
			return (get_intersect_sphere_for_shadows(intersect_point,
						direction, obj->sphere, intersect_dist, min_distance));
	}
	return (0);
}

int		check_intersect_for_shadows(t_vector3d intersect_point, t_vector3d direction,
		float min_distance, float max_distance, t_scene *scene)
{
	int         i;
	t_object3d  object;
	float       intersect_dist;

	intersect_dist = max_distance;
	i = -1;
	while (++i < scene->objects_num)
	{
		object = scene->objects[i];
		if (get_intersect_shadows(&object, intersect_point, direction, &intersect_dist, min_distance))
			return (1);
	}
	return (0);
}
