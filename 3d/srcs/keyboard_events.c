/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:31:12 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/03 23:28:10 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"

int	key_press(int key, t_conf *conf)
{
	if (key == 49)
	{
		conf->fractal.left_b /= 1.5;
		conf->fractal.right_b /= 1.5;
		conf->fractal.top_b /= 1.5;
		conf->fractal.bot_b /= 1.5;
		conf->fractal.front_b /= 1.5;
		conf->fractal.back_b /= 1.5;
		initialization_scene(conf);
	}
	if (key == 12)
		conf->canvas.y_rotation -= 0.1;
	else if (key == 14)
		conf->canvas.y_rotation += 0.1;
	else if (key == 13)
		conf->canvas.camera.z += 10;
	else if (key == 1)
		conf->canvas.camera.z -= 10;
	else if (key == 0)
		conf->canvas.camera.x -= 10;
	else if (key == 2)
		conf->canvas.camera.x += 10;
	else if (key == 126)
		conf->canvas.camera.y += 10;
	else if (key == 125)
		conf->canvas.camera.y -= 10;
	else if (key == 123)
		conf->canvas.min_distance -= 0.05;
	else if (key == 124)
		conf->canvas.min_distance += 0.05;
	else if (key == 53)
		ft_exit(conf);
	refresh(conf);
	return (0);
}
