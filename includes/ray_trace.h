/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:25:55 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 21:38:38 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACE_H
# define RAY_TRACE_H

# include "math_vec.h"
# include "utilits.h"

typedef struct	s_sphere
{
	t_vector3d	center;
	float		radius;
	float		sq_radius;
}				t_sphere;

typedef struct	s_object3d
{
	int			type;
	t_color		color;
	int			smoothness;
	float		reflectivity;
	t_sphere	sphere;
}				t_object3d;

typedef struct	s_lights
{
	int			type;
	float		intensity;
	t_vector3d	position;
	t_vector3d	direction;
	float		sqrt_scalar_direction;
}				t_lights;

typedef struct	s_canvas
{
	float		width;
	float		height;
	float		min_distance;
	float		max_distance;
	float		x_rotation;
	float		y_rotation;
	float		z_rotation;
	float		cos_x_rotate;
	float		sin_x_rotate;
	float		cos_y_rotate;
	float		sin_y_rotate;
	float		cos_z_rotate;
	float		sin_z_rotate;
	t_vector3d	camera;
}				t_canvas;

typedef struct	s_inicialization_object
{
	t_vector3d	center;
	float		radius;
	t_color		color;
	int			smoothness;
	float		reflectivity;
}				t_inicialization_object;

t_object3d		new_obj_sphere(t_inicialization_object sphere);
t_vector3d		get_normal_vector_sphere(t_sphere sphere,
		const t_vector3d intersection_point);
t_lights		new_light_ambient(float intensity);
t_lights		new_light_point(float intensity, t_vector3d position);
t_lights		new_light_directional(float intensity, t_vector3d direction);

#endif
