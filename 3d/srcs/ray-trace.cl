#include "config_cl.h"

t_vector3d  get_normal_vector(t_object3d *obj, t_vector3d intersect_point)
{
    if (obj->type == 1)
        return (get_normal_vector_sphere(obj->sphere, intersect_point));
    return (mv_get_vector3d(0, 0, 0));
}

int     get_intersect(t_vector3d *start_ray, t_vector3d *ray, t_object3d *obj,
			float *intersect_dist, float min_distance, float scalar_ray)
{
	if (obj->type == 1)
		return (get_intersect_sphere(*start_ray, *ray, obj->sphere, intersect_dist,
					min_distance, scalar_ray));
	return (0);
}

float       find_intersect(t_vector3d *start_ray, t_vector3d *ray,
				t_scene *scene, t_object3d *closest_obj, float scalar_ray)
{
	t_object3d object;
	int         i;
	float       intersect_dist;

	intersect_dist = scene->max_distance;
	i = -1;
	while (++i < scene->objects_num)
	{
		object = scene->objects[i];
		if (get_intersect(start_ray, ray, &object, &intersect_dist, scene->min_distance, scalar_ray))
			*closest_obj = object;
	}
	if (intersect_dist > scene->min_distance && intersect_dist < scene->max_distance)
		return (intersect_dist);
	else
		return (0);
}

t_vector3d	reflected_ray(t_vector3d ray, t_vector3d N)
{
	return (mv_plus(mv_mult_num(mv_mult_num(N, 2), mv_scalar_mult(mv_mult_num(ray, -1), N)), ray));
}

t_color     ray_trace(t_vector3d start_ray, t_vector3d ray, t_scene *scene)
{
	t_color		color;
	t_vector3d  intersect_point;
	float       intersect_dist;
	t_object3d  closest_obj;
	t_vector3d	normal;
	float		scal_ray_for_optimize;
	t_reflection reflection[DEPTH + 1];
	int			count;

	count = 0;
	int i = -1;
	while (++i <= DEPTH)
	{
		scal_ray_for_optimize = mv_scalar_mult(ray, ray);
		if ((intersect_dist = find_intersect(&start_ray, &ray, scene, &closest_obj, scal_ray_for_optimize)))
		{
			intersect_point = mv_plus(start_ray, mv_mult_num(ray, intersect_dist));
			normal = get_normal_vector(&closest_obj, intersect_point);
			color = rgb_mult_num(closest_obj.color,
					get_light_intensity(&closest_obj, intersect_point, scene, ray, normal));
			reflection[i].local_color = color;
			ray = reflected_ray(ray, normal);
			start_ray = intersect_point;
			++count;
			if (closest_obj.reflectivity == 0)
				break;
			reflection[i].reflectivity = closest_obj.reflectivity;
		}
		else
			break;
	}
	if (count > 0)
	{
		reflection[--count].reflectivity = 0;
		while (--count >= 0)
		{
			reflection[count].local_color =
					rgb_plus(rgb_mult_num(reflection[count].local_color, 1 - reflection[count].reflectivity),
					rgb_mult_num(reflection[count + 1].local_color, reflection[count].reflectivity));
		}
		return (reflection[0].local_color);
	}
	return (get_rgb(0 ,0 ,0));
}
