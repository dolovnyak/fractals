/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 22:17:48 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 22:17:50 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_vec.h"
#include <math.h>

t_vector3d	mv_mult_num(const t_vector3d a, float num)
{
	t_vector3d	c;

	c.x = a.x * num;
	c.y = a.y * num;
	c.z = a.z * num;
	return (c);
}

t_vector3d	mv_dev_num(const t_vector3d a, float num)
{
	t_vector3d	c;

	c.x = a.x / num;
	c.y = a.y / num;
	c.z = a.z / num;
	return (c);
}
