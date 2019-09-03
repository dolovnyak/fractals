#include "config_cl.h"

void		get_reflection(int smoothness, t_vector3d N, t_vector3d negative_ray,
				float *intensity, t_lights light)
{
	t_vector3d	reflection_ray;
	float		scalar_neg_reflect_ray;

	if (smoothness != -1)
	{
		reflection_ray = mv_minus(mv_mult_num(mv_mult_num(N, 2),
							mv_scalar_mult(N, light.direction)), light.direction);
		scalar_neg_reflect_ray = mv_scalar_mult(negative_ray, reflection_ray);
		if (scalar_neg_reflect_ray > 0)
			*intensity += light.intensity * pow(scalar_neg_reflect_ray /
					(mv_length(reflection_ray) * mv_length(negative_ray)), smoothness);
	}
}

float       get_light_intensity(t_object3d *obj, t_vector3d intersect_point,
				t_scene *scene, t_vector3d ray, t_vector3d N)
{
	float		max_distance;
	float       intensity;
	float       intensity_tmp;
	float		sqrt_scalar_N;
	t_lights    light;
	int         i;

	intensity = 0.0;
	i = -1;
	sqrt_scalar_N = sqrt(mv_scalar_mult(N, N));
	while (++i < scene->lights_num)
	{
		light = scene->lights[i];
		if (light.type == 1)
			intensity += light.intensity;
		else
		{
			if (light.type == 2)
			{
				light.direction = mv_minus(light.position, intersect_point);
				light.sqrt_scalar_direction = sqrt(mv_scalar_mult(light.direction, light.direction));
				max_distance = 1;
			}
			else
				max_distance = 999999;
			if (check_intersect_for_shadows(intersect_point, light.direction,
				0.001, max_distance, scene) == 0)
			{
				intensity_tmp = light.intensity * mv_scalar_mult(N, light.direction) /
					(sqrt_scalar_N * light.sqrt_scalar_direction);
				if (intensity_tmp > 0)
					intensity += intensity_tmp;
				get_reflection(obj->smoothness, N, mv_mult_num(ray, -1), &intensity, light);
			}
		}
	}
	return (intensity);
}
