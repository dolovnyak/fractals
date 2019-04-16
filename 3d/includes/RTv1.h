#ifndef RTV1_H
# define RTV1_H

#include "math_vec.h"

typedef struct	s_object3d
{
	void		*data;
	int			(*get_intersect)(const void *data, t_vector3d cam_ray_start,
			const t_vector3d cam_ray, float *intersect_dist);
	int			(*get_color)(const void *data, const t_vector3d intersection_point);
	t_vector3d	(*get_normal_vector)(const void *data,
			const t_vector3d intersection_point);
}				t_object3d;

typedef struct	s_sphere
{
	t_vector3d  center;
	float       radius;
	t_color     color;
}               t_sphere;

typedef struct	s_lights
{
	int			type;
	float		intensity;
	t_vector3d	position;
	t_vector3d	direction;
}				t_lights;

/* types:
 * 1 - ambient
 * 2 - point
 * 3 - directional
 */

t_object3d	*new_sphere(const t_vector3d center, const float radius, const t_color color);
int			get_intersect_sphere(const void *data, const t_vector3d camera,
		const t_vector3d canvas_cell, float *intersect_dist);
t_vector3d	get_normal_vector_sphere(const void *data, const t_vector3d intersection_point);

#endif
