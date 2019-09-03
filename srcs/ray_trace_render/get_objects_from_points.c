/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects_from_points.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 21:02:43 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 23:14:02 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal3d.h"
#include "config.h"

int						get_num_objects(t_fractal_point **all_points,
		int xy_len, int z_len)
{
	int				objects_num;
	register int	i;
	register int	j;

	ft_printf("\ngetting objects num...\n");
	objects_num = 0;
	i = -1;
	j = -1;
	while (++i < z_len)
	{
		while (++j < xy_len)
			if (all_points[i][j].flag == 1)
				objects_num++;
		j = -1;
	}
	ft_printf("objects num: %d\n", objects_num);
	return (objects_num);
}

t_inicialization_object	initialization_sphere(t_fractal_point point)
{
	t_inicialization_object	sphere;

	sphere.center = mv_get_vector3d(point.x, point.y, point.z);
	sphere.radius = 0.6;
	sphere.color = get_rgb(point.r, point.g, point.b);
	sphere.smoothness = 4;
	sphere.reflectivity = 0.7;
	return (sphere);
}

t_object3d				*get_objects(int objects_num,
		t_fractal_point **all_points, int xy_len, int z_len)
{
	t_object3d				*objects;
	register int			i;
	register int			j;
	register int			count;

	ft_printf("getting objects...\n");
	i = -1;
	j = -1;
	count = -1;
	objects = (t_object3d*)malloc(sizeof(t_object3d) * objects_num);
	while (++i < z_len)
	{
		while (++j < xy_len)
			if (all_points[i][j].flag == 1)
				objects[++count] =
					new_obj_sphere(initialization_sphere(all_points[i][j]));
		j = -1;
	}
	i = -1;
	while (++i < z_len)
		free(all_points[i]);
	free(all_points);
	ft_printf("objects obtained\n");
	return (objects);
}
