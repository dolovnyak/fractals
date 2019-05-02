#ifndef CONFIG_CL_H
# define CONFIG_CL_H

#include "math_vec.h"
#include "utilits.h"
#include "RTv1.h"

#define DEPTH 0

typedef struct  s_reflection
{
	t_color     local_color;
	float       reflectivity;
}               t_reflection;

typedef struct	s_scene
{
	int						objects_num;
	int						lights_num;
	float					min_distance;
	float					max_distance;
	__global t_object3d*	objects;
	__global t_lights*		lights;
}				t_scene;

t_vector3d	get_cam_ray(int x, int y, t_canvas canvas, int width, int height);
t_color		ray_trace(t_vector3d start_ray, t_vector3d ray, t_scene *scene);
float       find_intersect(t_vector3d *start_ray, t_vector3d *ray,
		t_scene *scene, t_object3d *closest_obj, float scalar_ray);
int			get_intersect(t_vector3d *start_ray, t_vector3d *ray, t_object3d *obj,
		float *intersect_dist, float min_distance, float scalar_ray);
int			get_intersect_sphere(t_vector3d start_ray, t_vector3d ray, t_sphere sphere,
		float *intersect_dist, float min_distance, float scalar_ray_for_optimize);
int			get_intersect_sphere_for_shadows(t_vector3d start_ray, t_vector3d ray,
		t_sphere sphere, float *intersect_dist, float min_distance);
float		get_light_intensity(t_object3d *obj, t_vector3d intersect_point,
		t_scene *scene, t_vector3d ray, t_vector3d N);
t_vector3d  get_normal_vector(t_object3d *obj, t_vector3d intersect_point);
void        put_pixel(int x, int y, t_color color, __global char* img, int width, int height);
void		get_reflection(int smoothness, t_vector3d N, t_vector3d negative_ray,
		float *intensity, t_lights light);
int			get_intersect_shadows(t_object3d *obj, t_vector3d intersect_point, 
		t_vector3d direction, float *intersect_dist, float min_distance);
int         check_intersect_for_shadows(t_vector3d intersect_point, t_vector3d direction,
		float min_distance, float max_distance, t_scene *scene);
t_vector3d	reflected_ray(t_vector3d ray, t_vector3d N);
t_vector3d	rotation(t_vector3d A, float cos_x_rotate, float sin_x_rotate,
		float cos_y_rotate, float sin_y_rotate, float cos_z_rotate, float sin_z_rotate);

#endif
