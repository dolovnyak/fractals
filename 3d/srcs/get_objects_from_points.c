/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 03:55:18 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/02 05:42:43 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int     get_num_objects(t_fractal_point **all_points, int xy_len, int z_len)
{
	int objects_num;
	register int    i;
	register int    j;

	printf("\ngetting objects num...\n");
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
	printf ("objects num: %d\n", objects_num);
	return (objects_num);
}

void    get_objects(t_conf *conf, t_fractal_point **all_points, int xy_len, int z_len)
{
	t_object3d      *objects;
	t_lights        lights;
	register int    i;
	register int    j;
	register int    count;

	printf ("getting objects...\n");
	i = -1;
	j = -1;
	count = -1;
	objects = (t_object3d*)malloc(sizeof(t_object3d) * conf->objects_num);
	while (++i < z_len)
	{
		while (++j < xy_len)
			if (all_points[i][j].flag == 1)
			{
				objects[++count] = new_obj_sphere(mv_get_vector3d(all_points[i][j].x,
						all_points[i][j].y, all_points[i][j].z), 0.5, get_rgb(255, 0, 0),
						100, 0, 0);
//				printf("%d / %d : (%f, %f, %f)\n", count, conf->objects_num, all_points[i][j].x,
//						all_points[i][j].y, all_points[i][j].z);
			}
		j = -1;
	}
	conf->objects = objects;
	i = -1;
	while (++i < z_len)
		free(all_points[i]);
	free(all_points);
	printf ("objects obtained\n");
}
