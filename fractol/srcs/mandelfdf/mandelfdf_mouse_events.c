/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelfdf_mouse_events.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:09:29 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 10:57:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandelfdf.h"

int		mandelfdf_mouse_press(int button, int x, int y, t_mandelfdf *conf)
{
	double  comp_x;
	double  comp_y;
	double	dx, dy, tmp_x;

	dx = conf->zoom * (x - conf->mlx->width / 2);
	dy = conf->zoom * (y - conf->mlx->height / 2);
	tmp_x = conf->center_x + dx * cos(conf->angle_z) - dy * sin(conf->angle_z);
	dy = conf->center_y - dy * cos(conf->angle_z) + dx * sin(conf->angle_z);
	dx = tmp_x;
	if (button == 4 && conf->control_flag == 1)
	{
		comp_x = (conf->right_b - conf->left_b) / conf->mlx->width * dx;
		comp_y = (conf->bot_b - conf->top_b) / conf->mlx->height * dy;
		conf->left_b = conf->left_b + comp_x /8;
		conf->right_b = conf->right_b - ((conf->right_b - conf->left_b) - comp_x) / 8;
		conf->top_b = conf->top_b + comp_y / 8;
		conf->bot_b = conf->bot_b - ((conf->bot_b - conf->top_b) - comp_y) / 8;
		//	conf->up_height += 0.5;
	}
	else if (button == 4)
		conf->zoom += 1;
	if (button == 5 && conf->control_flag == 1)
	{
		comp_x = (conf->right_b - conf->left_b) / 8;
		comp_y = (conf->bot_b - conf->top_b) / 8;
		conf->left_b -= comp_x;
		conf->right_b += comp_x;
		conf->top_b -= comp_y;
		conf->bot_b += comp_y;
		//	conf->up_height -= 0.5;
	}
	else if (button == 5 && conf->zoom > 1)
		conf->zoom -= 1;
	if (button == 1 && conf->button_flag == 0)
	{
		conf->button_flag = 1;
		conf->mouse_x = x;
		conf->mouse_y = y;
	}
	return (0);
}

int		mandelfdf_mouse_release(int button, int x, int y, t_mandelfdf *conf)
{
	if (button == 1)
		conf->button_flag = 0;
	x = 0;
	y = 0;
	return (0);
}

int		mandelfdf_mouse_move(int x, int y, t_mandelfdf *conf)
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
		if (y < conf->mouse_y && conf->angle_x >= 0)
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
