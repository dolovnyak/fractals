/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_keyboard_events.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 08:40:28 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/16 21:09:27 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	fractal_change(int key, t_render *conf)
{
	if (key == 49)
	{
		conf->fractal->left_b /= 1.1;
		conf->fractal->right_b /= 1.1;
		conf->fractal->top_b /= 1.1;
		conf->fractal->bot_b /= 1.1;
		conf->fractal->front_b /= 1.1;
		conf->fractal->back_b /= 1.1;
	}
	else if (key == 43)
		conf->fractal->const_x -= 0.01;
	else if (key == 47)
		conf->fractal->const_x += 0.01;
	else if (key == 37)
		conf->fractal->const_iy -= 0.01;
	else if (key == 41)
		conf->fractal->const_iy += 0.01;
	else if (key == 33)
		conf->fractal->const_jz -= 0.01;
	else if (key == 30)
		conf->fractal->const_jz += 0.01;
	free(conf->objects);
	free(conf->lights);
	initialization_scene(conf);
}

static void	common_events(int key, t_render *conf)
{
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
	else if (key == 49 || key == 43 || key == 47 || key == 37 ||
			key == 41 || key == 33 || key == 30)
		fractal_change(key, conf);
	else if (key == 53)
		exit_event(conf->cl);
}

int			rt_key_press_safety(int key, t_render *conf)
{
	common_events(key, conf);
	refresh_rt_safety(conf);
	return (0);
}

int			rt_key_press_fast(int key, t_render *conf)
{
	common_events(key, conf);
	refresh_rt_fast(conf);
	return (0);
}
