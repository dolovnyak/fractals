#include "config_cl.h"

int		get_intersect_sphere(t_vector3d start_ray, t_vector3d ray, t_sphere sphere,
			float *intersect_dist, float min_distance, float scalar_ray_for_optimize)
{
	float		intersect_dist1;
	float		intersect_dist2;
	float		k1, k2, k3;
	t_vector3d	OC;
	float		discriminant;
	float		sq_discriminant;
	float		intersect_tmp;

	intersect_tmp = *intersect_dist;
	OC = mv_minus(start_ray, sphere.center);
	k1 = scalar_ray_for_optimize;
	k2 = 2 * mv_scalar_mult(OC, ray);
	k3 = mv_scalar_mult(OC, OC) - sphere.sq_radius;
	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
		return(0);
	sq_discriminant = sqrt(discriminant);
	intersect_dist1 = (-k2 + sq_discriminant) / (2 * k1);
	intersect_dist2 = (-k2 - sq_discriminant) / (2 * k1);
	if (intersect_dist1 < *intersect_dist && intersect_dist1 > min_distance)
		*intersect_dist = intersect_dist1;
	if (intersect_dist2 < *intersect_dist && intersect_dist2 > min_distance)
		*intersect_dist = intersect_dist2;
	if (*intersect_dist == intersect_tmp)
		return (0);
	return (1);
}

int		get_intersect_sphere_for_shadows(t_vector3d start_ray, t_vector3d ray,
			t_sphere sphere, float *intersect_dist, float min_distance)
{
	float		intersect_dist1;
	float		intersect_dist2;
	float		k1, k2, k3;
	t_vector3d	OC;
	float		discriminant;
	float		sq_discriminant;
	float		intersect_tmp;

	intersect_tmp = *intersect_dist;
	OC = mv_minus(start_ray, sphere.center);
	k1 = mv_scalar_mult(ray, ray);
	k2 = 2 * mv_scalar_mult(OC, ray);
	k3 = mv_scalar_mult(OC, OC) - sphere.sq_radius;
	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
		return(0);
	sq_discriminant = sqrt(discriminant);
	intersect_dist1 = (-k2 + sq_discriminant) / (2 * k1);
	intersect_dist2 = (-k2 - sq_discriminant) / (2 * k1);
	if (intersect_dist1 < *intersect_dist && intersect_dist1 > min_distance)
		*intersect_dist = intersect_dist1;
	if (intersect_dist2 < *intersect_dist && intersect_dist2 > min_distance)
		*intersect_dist = intersect_dist2;
	if (*intersect_dist == intersect_tmp)
		return (0);
	return (1);
}

t_vector3d	get_normal_vector_sphere(t_sphere sphere, const t_vector3d intersection_point)
{
	t_vector3d	N;

	N = mv_minus(intersection_point, sphere.center);
	N = mv_dev_num(N, sqrt(mv_scalar_mult(N, N)));
	return (N);
}
