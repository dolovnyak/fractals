/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:31:12 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/02 06:20:55 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int	key_press(int key, t_conf *conf)
{
/*	if (key == 12)
		conf->flag_rotation_z_left = 1;
	else if (key == 14)
		conf->flag_rotation_z_right = 1;*/
	if (key == 13)
		conf->canvas.camera.z += 0.5;
	else if (key == 1)
		conf->canvas.camera.z -= 0.5;
	else if (key == 0)
		conf->canvas.camera.x -= 0.5;
	else if (key == 2)
		conf->canvas.camera.x += 0.5;
	else if (key == 126)
		conf->canvas.camera.y += 0.5;
	else if (key == 125)
		conf->canvas.camera.y -= 0.5;
	else if (key == 123)
		conf->canvas.min_distance -= 0.05;
	else if (key == 124)
		conf->canvas.min_distance += 0.05;
	else if (key == 53)
		exit(0);
//	refresh(conf);
	return (0);
}

/*int	key_release(int key, t_conf *conf)
{
	if (key == 12)
		conf->flag_rotation_z_left = 0;
	if (key == 14)
		conf->flag_rotation_z_right = 0;
	return (0);
}*/
