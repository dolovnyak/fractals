/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:14:38 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/03 02:44:09 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

t_object3d	new_obj_sphere(const t_vector3d center, const float radius,
		const t_color color, const int smoothness, float reflectivity)
{
	t_object3d	object;

	object.type = 1;
	object.color = color;
	object.smoothness = smoothness;
	object.reflectivity = reflectivity;
	object.sphere.center = center;
	object.sphere.radius = radius;
	object.sphere.sq_radius = radius * radius;
	return (object);
}