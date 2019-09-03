/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:14:38 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 21:33:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

t_object3d	new_obj_sphere(t_inicialization_object sphere)
{
	t_object3d	object;

	object.type = 1;
	object.color = sphere.color;
	object.smoothness = sphere.smoothness;
	object.reflectivity = sphere.reflectivity;
	object.sphere.center = sphere.center;
	object.sphere.radius = sphere.radius;
	object.sphere.sq_radius = sphere.radius * sphere.radius;
	return (object);
}
