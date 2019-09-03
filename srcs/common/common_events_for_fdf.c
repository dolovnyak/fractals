/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_common_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 16:34:20 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/11 17:57:27 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractalfdf.h"

int		commonfdf_keyboard_press(int keycode, t_fractalfdf *conf)
{
	if (keycode == 53)
		exit_event(conf->fractal.cl);
	if (conf->shift_flag == 1 || keycode == 123 || keycode == 124 ||
			keycode == 49)
		common2d_key_press(keycode, &conf->fractal);
	else if (keycode == 0)
		conf->center_x += 20;
	else if (keycode == 2)
		conf->center_x -= 20;
	else if (keycode == 1)
		conf->center_y -= 20;
	else if (keycode == 13)
		conf->center_y += 20;
	else if (keycode == 12)
		conf->angle_z -= 0.05;
	else if (keycode == 14)
		conf->angle_z += 0.05;
	else if (keycode == 257)
		conf->shift_flag = 1;
	return (0);
}

int		commonfdf_key_release(int keycode, t_fractalfdf *conf)
{
	if (keycode == 257)
		conf->shift_flag = 0;
	return (0);
}

int		commonfdf_mouse_release(int button, int x, int y, t_fractalfdf *conf)
{
	if (button == 1)
		conf->button_flag = 0;
	x = 0;
	y = 0;
	return (0);
}

int		commonfdf_mouse_press(int button, int x, int y, t_fractalfdf *conf)
{
	if (conf->shift_flag == 1)
		common2d_mouse_press(button, x, y, &conf->fractal);
	else if (button == 4)
		conf->zoom += 1;
	else if (button == 5 && conf->zoom > 1)
		conf->zoom -= 1;
	else if (button == 1 && conf->button_flag == 0)
	{
		conf->button_flag = 1;
		conf->mouse_x = x;
		conf->mouse_y = y;
	}
	return (0);
}

int		commonfdf_mouse_move(int x, int y, t_fractalfdf *conf)
{
	if (conf->button_flag == 1)
	{
		if (x < conf->mouse_x)
		{
			conf->angle_z += 0.05;
			conf->mouse_x = x;
		}
		else if (x > conf->mouse_x)
		{
			conf->angle_z -= 0.05;
			conf->mouse_x = x;
		}
		else if (y < conf->mouse_y && conf->angle_x >= 0)
		{
			conf->angle_x -= 0.02;
			conf->mouse_y = y;
		}
		else if (y > conf->mouse_y && conf->angle_x <= 3.14159)
		{
			conf->angle_x += 0.02;
			conf->mouse_y = y;
		}
	}
	return (0);
}
