/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_common_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 13:58:07 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/11 17:22:31 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal2d.h"

static void	get_length_accord_norm(t_fractal2d *conf, double *dx, double *dy)
{
	*dx = (conf->right_b - conf->left_b);
	*dy = (conf->bot_b - conf->top_b);
}

int			common2d_mouse_press(int button, int x, int y, t_fractal2d *conf)
{
	double	comp_x;
	double	comp_y;
	double	dx;
	double	dy;

	get_length_accord_norm(conf, &dx, &dy);
	if (button == 4 || button == 6)
	{
		comp_x = dx / conf->mlx->width * x;
		comp_y = dy / conf->mlx->height * y;
		conf->left_b = conf->left_b + comp_x / 8;
		conf->right_b = conf->right_b - (dx - comp_x) / 8;
		conf->top_b = conf->top_b + comp_y / 8;
		conf->bot_b = conf->bot_b - (dy - comp_y) / 8;
	}
	else if (button == 5 || button == 7)
	{
		comp_x = dx / 8;
		comp_y = dy / 8;
		conf->left_b -= comp_x;
		conf->right_b += comp_x;
		conf->top_b -= comp_y;
		conf->bot_b += comp_y;
	}
	return (0);
}

static void	key_press_norm(int keycode, t_fractal2d *conf, double tmp)
{
	double	comp_x;
	double	comp_y;

	if (keycode == 2)
	{
		conf->right_b += tmp / conf->mlx->relation;
		conf->left_b += tmp / conf->mlx->relation;
	}
	else if (keycode == 0)
	{
		conf->right_b -= tmp / conf->mlx->relation;
		conf->left_b -= tmp / conf->mlx->relation;
	}
	else if (keycode == 49)
	{
		comp_x = (conf->right_b - conf->left_b) / 100;
		comp_y = (conf->bot_b - conf->top_b) / 100;
		conf->left_b -= comp_x;
		conf->right_b += comp_x;
		conf->top_b -= comp_y;
		conf->bot_b += comp_y;
	}
}

int			common2d_key_press(int keycode, t_fractal2d *conf)
{
	double	tmp;

	tmp = (conf->right_b - conf->left_b) / (conf->radius * 2);
	if (keycode == 53)
		exit_event(conf->cl);
	if (keycode == 123)
		conf->color_mult -= 100;
	else if (keycode == 124)
		conf->color_mult += 100;
	else if (keycode == 13)
	{
		conf->top_b -= tmp;
		conf->bot_b -= tmp;
	}
	else if (keycode == 1)
	{
		conf->bot_b += tmp;
		conf->top_b += tmp;
	}
	else
		key_press_norm(keycode, conf, tmp);
	return (0);
}
